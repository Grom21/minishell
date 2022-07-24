#include "minishell.h"

int	ft_found_redirect_in_command(t_shell *mini, t_lexer *lexer)
{
	t_lexer	*copy;

	copy = lexer;
	while (copy && copy->chank[0] != '|')
	{
		if (copy->chank[0] == '<' || copy->chank[0] == '>')
			return (1);
		copy = copy->next;
	}
	return (0);
}

int	found_heredoc(t_lexer *lexer)
{
	t_lexer *copy;

	copy = lexer;
	while (copy && copy->chank[0] != '|')
	{
		if (copy->chank[0] == '<' && copy->chank[1] == '<')
			return (-3);
		copy = copy->next;
	}
	return (g_last_exit);
}

void	ft_exit_with_redirect(t_shell *mini, t_lexer *copy, int count, int i)
{
	int	result;

	if (count == -1 && copy && ft_strcmp("exit", copy->chank) == 0 \
	&& ft_found_redirect_in_command(mini, copy) != 0)
	{
		// if (ft_found_redirect_in_command(mini, copy) != 0)
			ft_redirect(mini, copy, i, count);
		if ((result = ft_found_in_castom(mini, copy)) != -1)
			exit (result);
	}
}
