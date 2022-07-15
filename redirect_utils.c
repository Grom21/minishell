#include "minishell.h"

void	ft_run_redirect(t_shell *mini, t_lexer *lexer, int *fd)
{
	int	result;

	if (fd[0] != 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (fd[1] != 1)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if ((result = ft_found_in_castom(mini, lexer)) != -1)
		exit (result);
	ft_run_from_path(mini, lexer);
	if (lexer->chank[0] == '.' || lexer->chank[0] == '/' || lexer->chank[0] == '~')
		ft_print_parser_error(&lexer,  NO_SUCH_FILE_OR_DIR);
	else
		ft_print_parser_error(&lexer, COMMAND_NOT_FOUND);
}
