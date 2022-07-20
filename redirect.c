#include "minishell.h"

static int	ft_redirect_in_file1(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == EROFS)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static int	ft_redirect_in_file2(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == EROFS)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static int	ft_redirect_out_file1(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_RDONLY, 0666);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit (ft_redirect_error(&now->next, IS_A_DIRECTORY));
		else if (errno == EACCES)
			exit (ft_redirect_error(&now->next, PERMISSION_DENIED));
		else if (errno == ENOENT)
			exit (ft_redirect_error(&now->next, NO_SUCH_FILE_OR_DIR));
		else if (errno == ETXTBSY)
			exit (ft_redirect_error(&now->next, FILE_IS_BUSY));
		else
			exit (ft_redirect_error(&now->next, OTHER_ERROR));
	}
	return (fd);
}

static int	ft_redirect_out_file2(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int		fd;
	char	*str;

	fd = ft_open_heredoc(lexer, 0);
	g_last_exit = -2;
	dup2(0, 0);
	str = readline("> ");
	if (ft_strcmp(str, now->next->chank) == 0)
		return (0);
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

void	ft_redirect(t_shell *mini, t_lexer *lexer)
{
	t_lexer	*copy;
	int		result;
	int		fd[2];

	fd[0] = 0;
	fd[1] = 1;
	copy = lexer;
	while (copy && copy->chank[0] != '|')
	{
		if (copy->chank[0] == '>' && copy->chank[1] == '\0')
			fd[1] = ft_redirect_in_file1(mini, lexer, copy);
		else if (copy->chank[0] == '>' && copy->chank[1] == '>')
			fd[1] = ft_redirect_in_file2(mini, lexer, copy);
		else if (copy->chank[0] == '<' && copy->chank[1] == '\0')
			fd[0] = ft_redirect_out_file1(mini, lexer, copy);
		else if (copy->chank[0] == '<' && copy->chank[1] == '<')
		{
			fd[0] = ft_redirect_out_file2(mini, lexer, copy);
		}
		copy = copy->next;
	}
	ft_run_redirect(mini, lexer, fd);
}
