#include "minishell.h"

void	ft_print_parser_error(t_lexer **lexer, int exeption)
{
	t_lexer *copy;

	copy = *lexer;
	if (exeption == SYNTAX_ERROR)
	{
		write(2, "minishell: syntax error\n", 24);
	}
	else if (exeption == COMMAND_NOT_FOUND)
	{
		write(2, "minishell: ", 11);
		write(2, copy->chank, ft_strlen(copy->chank));
		write(2, ": command not found\n", 20);
	}
	else if (exeption == SYNTAX_PIPE_ERROR)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
}
