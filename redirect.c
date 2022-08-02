/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:31 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 12:07:19 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redirect_in_file1(t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == EROFS)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static int	ft_redirect_in_file2(t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == EROFS)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static int	ft_redirect_out_file1(t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_RDONLY, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static t_lexer	*work_fd(t_lexer *lexer, t_lexer *copy, int *fd)
{
	if (copy->chank[0] == '>' && copy->chank[1] == '\0')
		fd[1] = ft_redirect_in_file1(copy);
	else if (copy->chank[0] == '>' && copy->chank[1] == '>')
		fd[1] = ft_redirect_in_file2(copy);
	else if (copy->chank[0] == '<' && copy->chank[1] == '\0')
		fd[0] = ft_redirect_out_file1(copy);
	else if (copy->chank[0] == '<' && copy->chank[1] == '<')
		fd[0] = ft_redirect_out_file2(lexer, copy);
	copy = copy->next;
	return (copy);
}

void	ft_redirect(t_shell *mini, t_lexer *lexer, int i, int count)
{
	t_lexer	*copy;
	int		fd[2];
	int		flag;

	fd[0] = 0;
	fd[1] = 1;
	copy = lexer;
	flag = 0;
	if (i != -1 && found_heredoc(lexer) != -3)
	{
		ft_work_with_fd(mini, i, count);
		ft_work_with_fd_last_command(mini, i, count);
		flag = 1;
	}
	while (copy && copy->chank[0] != '|')
		copy = work_fd(lexer, copy, fd);
	if (i != -1 && flag == 0)
	{
		ft_work_with_fd(mini, i, count);
		ft_work_with_fd_last_command(mini, i, count);
	}
	ft_run_redirect(mini, lexer, fd);
}
