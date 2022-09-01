/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:01:19 by etisha            #+#    #+#             */
/*   Updated: 2022/08/04 15:35:46 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_found_funct(t_lexer *lexer, int i, t_shell *mini)
{
	if (i == 0)
		return (ft_echo(lexer));
	else if (i == 1)
		return (ft_cd(lexer, mini));
	else if (i == 2)
		return (ft_pwd());
	else if (i == 3)
		return (ft_export(lexer, mini->envp_list));
	else if (i == 4)
		return (ft_unset(lexer, &mini->envp_list));
	else if (i == 5)
		return (ft_env(mini->envp_list));
	else if (i == 6)
		return (ft_exit(mini, lexer));
	return (0);
}

void	ft_work_with_fd(t_shell *mini, int i, int count)
{
	if (i == 0)
	{
		dup2(mini->fd1[1], 1);
		close(mini->fd1[1]);
	}
	else if (i < count && (i % 2) != 0)
	{
		dup2(mini->fd1[0], 0);
		dup2(mini->fd2[1], 1);
		close(mini->fd1[0]);
		close(mini->fd2[1]);
	}
	else if (i < count && (i % 2) == 0)
	{
		dup2(mini->fd2[0], 0);
		dup2(mini->fd1[1], 1);
		close(mini->fd2[0]);
		close(mini->fd1[1]);
	}
}

void	ft_work_with_fd_last_command(t_shell *mini, int i, int count)
{
	if (i == count && (i % 2) != 0)
	{
		dup2(mini->fd1[0], 0);
		close(mini->fd1[0]);
	}
	else if (i == count && (i % 2) == 0)
	{
		dup2(mini->fd2[0], 0);
		close(mini->fd2[0]);
	}
}

int	ft_found_in_castom(t_shell *mini, t_lexer *lexer)
{
	t_lexer	*copy;
	int		i;
	int		result;

	copy = lexer;
	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(copy->chank, mini->comand[i]) == 0)
		{
			result = ft_found_funct(copy, i, mini);
			return (result);
		}
	}
	return (-1);
}

void	ft_children_run(t_shell *mini, t_lexer *lexer, int i, int count)
{
	int	result;

	ft_free_memory_matrix(mini->envp);
	mini->envp = ft_new_envp(&mini->envp_list);
	if (mini->envp == NULL)
		exit (1);
	if (ft_found_redirect_in_command(lexer) != 0)
		ft_redirect(mini, lexer, i, count);
	if (i != -1)
	{
		ft_work_with_fd(mini, i, count);
		ft_work_with_fd_last_command(mini, i, count);
	}
	result = ft_found_in_castom(mini, lexer);
	if (result != -1)
		exit (result);
	ft_run_from_path(mini, lexer);
	if ((lexer->chank[0] == '.' && lexer->chank[1] == '/') || \
	lexer->chank[0] == '/' || lexer->chank[0] == '~')
		ft_print_parser_error(&lexer, NO_SUCH_FILE_OR_DIR);
	else
		ft_print_parser_error(&lexer, COMMAND_NOT_FOUND);
	exit (127);
}
