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
		close(fd[1]);
	}
	if (!lexer || lexer->chank[0] == '<' || lexer->chank[0] == '>')
		exit (EXIT_SUCCESS);
	result = ft_found_in_castom(mini, lexer);
	if (result != -1)
		exit (result);
	ft_run_from_path(mini, lexer);
	if (lexer->chank[0] == '.' || lexer->chank[0] == '/' \
	|| lexer->chank[0] == '~')
		ft_print_parser_error(&lexer, NO_SUCH_FILE_OR_DIR);
	else
		ft_print_parser_error(&lexer, COMMAND_NOT_FOUND);
}

int	ft_open_heredoc(t_lexer *lexer, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open("/tmp/heredoc_mini", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		fd = open("/tmp/heredoc_mini", O_RDONLY, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&lexer, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&lexer, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&lexer, NO_SUCH_FILE_OR_DIR));
		else if (errno == EROFS)
			exit (ft_redirect_error(&lexer, PERMISSION_DENIED));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&lexer, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&lexer, OTHER_ERROR));
	}
	return (fd);
}

int	ft_redirect_out_file2(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int		fd;
	char	*str;

	fd = ft_open_heredoc(lexer, 0);
	g_last_exit = -2;
	dup2(0, 0);
	str = readline("> ");
	while (ft_strcmp(str, now->next->chank) != 0)
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free (str);
		str = readline("> ");
	}
	free (str);
	close(fd);
	fd = ft_open_heredoc(lexer, 1);
	return (fd);
}
