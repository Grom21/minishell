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
