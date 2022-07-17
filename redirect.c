#include "minishell.h"

static int	ft_redirect_in_file1(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return(fd);
}

static int	ft_redirect_in_file2(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return(fd);
}

static int	ft_redirect_out_file1(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int	fd;

	fd = open(now->next->chank, O_RDONLY, 0666);
	// if (EDQUOT)		//The file does not exist!!!!!!!!!! exit (1);!
	// {
	// 	printf("The file does not exist!\n"); //test
	// 	exit (1);
	// }
	return(fd);
}

static int	ft_redirect_out_file2(t_shell *mini, t_lexer *lexer, t_lexer *now)
{
	int		fd;
	char	*str;

	fd = open("/tmp/heredoc_mini", O_CREAT | O_WRONLY | O_TRUNC, 0666);

	g_last_exit = -2; //test
	dup2(0, 0);
	str = readline("> ");
	if (ft_strcmp(str, now->next->chank) == 0)
		return(0);
	while (ft_strcmp(str, now->next->chank) != 0)
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free (str);
		str = readline("> ");
	}
	free (str);
	close(fd);
	fd = open("/tmp/heredoc_mini", O_RDONLY, 0666);
	return (fd);
}

void	ft_redirect(t_shell *mini, t_lexer *lexer)
{
	t_lexer *copy;
	int		result;
	int		fd[2];

	fd[0] = 0;
	fd[1] = 1;
	copy = lexer;
	while (copy)
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
