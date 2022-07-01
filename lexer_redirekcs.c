#include "minishell.h"

void	ft_lexer_run_space(t_lexer **lexer, char *input, int *start, int *stop)
{
	*start = 0;
	*stop = 0;
	while (input[(*start)] == ' ')
		(*start)++;
	*stop = *start;
	if (input[(*start)] == '\0')
		ft_create_lexer(lexer, input, *start, *stop);
}

void	ft_lexer_redirect(t_lexer **lexer, char *input, int *start, int *stop)
{
	(*stop)++;
	if ((input[(*stop)] == '<' && input[(*stop) - 1] == '<') \
	|| (input[(*stop)] == '>' && input[(*stop) - 1] == '>'))
		(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}
