#include "minishell.h"

static char	**ft_start_another_program(t_shell *mini, t_lexer *copy)
{
	struct stat	buf;
	char		**matrix;
	char		*buffer;
	char		*buffer2;

	if (copy->next && copy->next->chank[0] != '|')
	{
		if ((buffer = ft_strjoin(copy->chank, " ")) == NULL \
		|| (buffer2 = ft_strjoin(buffer, copy->next->chank)) == NULL)
			exit (1);		//????????????
		free (buffer);
		if ((matrix = ft_split(buffer2, ' ')) == NULL)
			exit (1);		//????????????
		free (buffer2);
	}
	else
	{
		if ((matrix = ft_split(copy->chank, ' ')) == NULL)
			exit (1);		//????????????
	}
	if (stat(copy->chank, &buf) == 0)	// if no writes?
		execve(copy->chank, matrix, mini->envp);
	return (matrix);
}

static t_list *ft_found_path(t_list *envp_list, t_lexer *copy)
{
	t_list		*envp_copy;

	envp_copy = envp_list;
	while (envp_copy)
	{
		if (ft_strcmp(envp_copy->key, "PATH") == 0)
			break ;
		envp_copy = envp_copy->next;
	}
	if (!envp_copy)
	{
		ft_print_parser_error(&copy, NO_SUCH_FILE_OR_DIR);
		exit (127);
	}
	return (envp_copy);
}

static char	**ft_create_path_matrix(t_lexer *copy, t_list *envp_copy)
{
	char	**path_matrix;
	char	*buffer;
	char	*buffer2;
	int		i;

	path_matrix = ft_split(envp_copy->value, ':');
	if (!path_matrix)
		exit (1);		//??????
	i = 0;
	while (path_matrix[i])
	{
		if ((buffer = ft_strjoin(path_matrix[i], "/")) == NULL \
		|| (buffer2 = ft_strjoin(buffer, copy->chank)) == NULL)
			exit (1);		//??????
		free (path_matrix[i]);
		free (buffer);
		path_matrix[i] = buffer2;
		i++;
	}
	return (path_matrix);
}

static void	start_in_path(char **path, t_lexer *copy, char **argv, char **envp)
{
	int			i;
	struct stat	buf;

	i = 0;
	while (path[i])
	{
		if (stat(path[i], &buf) == 0)
		{
			if (execve(path[i],argv, envp) == -1)
			{
				write (2, "error execve!\n", 14);		// ??????
				exit (127);			// ??????
			}
		}
		i++;
	}
	ft_free_memory_matrix(path);
	ft_free_memory_matrix(argv);
}

void	ft_run_from_path(t_shell *mini, t_lexer *copy)
{
	t_list	*envp_copy;
	char	**path_matrix;
	char	**argv;

	argv = ft_start_another_program(mini, copy);
	envp_copy = ft_found_path(mini->envp_list, copy);
	path_matrix = ft_create_path_matrix(copy, envp_copy);
	start_in_path(path_matrix, copy, argv, mini->envp);
}
