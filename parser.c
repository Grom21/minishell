#include "minishell.h"

static int	ft_exam_syntax_single_command(t_shell *mini)
{
	t_lexer	*copy;
	char	**command;
	int		i;

	copy = mini->lexer;
	while (copy)
	{
		if ((copy->chank[0] == '|') || (copy->chank[0] == '\0') \
		|| (copy->chank[0] == ';' && copy->next != NULL))
			return (0);
		copy = copy->next;
	}
	copy = mini->lexer;
	command = mini->comand;
	i = 0;
	while (i < 11)
	{
		if (ft_strcmp(copy->chank, command[i]) == 0)
			return (0);
		i++;
	}
	if (copy->chank[0] == '$')
		return (0);
	ft_print_parser_error(&mini->lexer, COMMAND_NOT_FOUND);
	return (COMMAND_NOT_FOUND);
}
// первый блок + блоки после | и ; должны быть командой или редиректом или $

int	ft_parser(t_shell *mini)
{
	int	result;

	if ((result = ft_exam_pipe_first_last_double(mini)) != 0)
		return (result);
	if ((result = ft_exam_backslash(mini)) != 0)
		return (result);
	if ((result = ft_exam_syntax_quotes(mini)) != 0)
		return (result);
	if ((result = ft_exam_double_redirect(mini)) != 0)
		return (result);
	if ((result = ft_exam_syntax_single_command(mini)) != 0)
		return (result);



	return (0);
}
