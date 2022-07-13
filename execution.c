#include "minishell.h"

static t_lexer	*ft_next_command(t_lexer *copy)
{
	while (copy && copy->chank[0] != '|')
		copy = copy->next;
	if (copy)
		copy = copy->next;
	return (copy);
}

static int	ft_found_command_with_pipe(t_lexer *lexer)
{
	t_lexer	*copy;
	int		i;

	copy = lexer;
	i = 0;
	while (copy)
	{
		if (copy->chank[0] == '|')
			i++;
		copy = copy->next;
	}
	if (i == 0)
		return (-1);
	else
		return (i);
}

static t_lexer	*ft_close_fd_and_wait(t_shell *mini, t_lexer *copy, int i, int count)
{
	if (i != -1)
	{
		if ((i % 2) == 0)
		{
			close(mini->fd1[1]);
			close(mini->fd2[0]);
		}
		else if ((i % 2) != 0)
		{
			close(mini->fd1[0]);
			close(mini->fd2[1]);
		}
	}
	waitpid(-1, &g_last_exit, 0);
	g_last_exit = g_last_exit / 255;
	return (ft_next_command(copy));
}

static int	ft_open_fd(t_shell *mini, int i, int count)
{
	i++;
	if ((i % 2) == 0 && i != count)
		pipe(mini->fd1);		//error?!
	else if ((i % 2) != 0)
		pipe(mini->fd2);
	return (i);
}

void	ft_execution(t_shell *mini)
{
	t_lexer	*copy;
	int		count;
	int		i;
	pid_t	children;

	copy = mini->lexer;
	count = ft_found_command_with_pipe(mini->lexer);
	i = -1;
	while (copy)
	{
		if (count > 0)
			i = ft_open_fd(mini, i, count);
		if (count == -1 && ft_found_redirect_in_command(mini, copy) == 0)
		{
			if ((g_last_exit = ft_found_in_castom(mini, copy)) != -1)
				break ;
		}
		children = fork();
		if (children < 0)
			break ;	// need write error massage! and close fd!
		else if (children == 0)
			ft_children_run(mini, copy, i, count);
		else
			copy = ft_close_fd_and_wait(mini, copy, i, count);
	}
}
