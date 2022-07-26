#include "minishell.h"

void	ft_close_fd(t_shell *mini, int i)
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
}

void	ft_error_fork(t_shell *mini, int i)
{
	g_last_exit = 1;
	write(2, "minishell: error fork!\n", 24);
	ft_close_fd(mini, i);
}

int	ft_found_command_with_pipe(t_lexer *lexer)
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
