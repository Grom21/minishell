/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:12 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:02:13 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*ft_next_command(t_lexer *copy)
{
	while (copy && copy->chank[0] != '|')
		copy = copy->next;
	if (copy)
		copy = copy->next;
	return (copy);
}

static t_lexer	*ft_wait(t_shell *mini, t_lexer *copy, int i)
{
	struct stat	buf;

	ft_close_fd(mini, i);
	g_last_exit = found_heredoc(copy);
	waitpid(-1, &g_last_exit, 0);
	if (g_last_exit == 2)
		g_last_exit = 130;
	else if (g_last_exit == 3)
	{
		write (2, "^\\Quit: 3\n", 10);
		g_last_exit = 131;
	}
	else
		g_last_exit = g_last_exit / 255;
	if (stat("/tmp/heredoc_mini", &buf) == 0)
		unlink("/tmp/heredoc_mini");
	return (ft_next_command(copy));
}

static int	ft_open_fd(t_shell *mini, int i, int count)
{
	i++;
	if ((i % 2) == 0 && i != count)
		pipe(mini->fd1);
	else if ((i % 2) != 0)
		pipe(mini->fd2);
	return (i);
}

static int	ft_execution_fork(t_shell *mini, t_lexer *copy, int i, int count)
{
	mini->children = fork();
	if (mini->children < 0)
	{
		ft_error_fork(mini, i);
		return (1);
	}
	else if (mini->children == 0)
	{
		g_last_exit = -1;
		ft_children_run(mini, copy, i, count);
	}
	return (0);
}

void	ft_execution(t_shell *mini)
{
	t_lexer	*copy;
	int		count;
	int		i;

	copy = mini->lexer;
	count = ft_found_command_with_pipe(mini->lexer);
	i = -1;
	ft_exit_with_redir(mini, copy, count, 0);
	while (copy)
	{
		if (count > 0)
			i = ft_open_fd(mini, i, count);
		if (count == -1 && ft_found_redirect_in_command(copy) == 0)
		{
			g_last_exit = ft_found_in_castom(mini, copy);
			if (g_last_exit != -1)
				break ;
		}
		if (ft_execution_fork(mini, copy, i, count) != 0)
			return ;
		copy = ft_wait(mini, copy, i);
	}
}
