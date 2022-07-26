#include "minishell.h"

static void	start_another_program(t_shell *mini, t_lexer *copy, char **argv)
{
	struct stat	buf;
	char		*file;

	if (stat(copy->chank, &buf) == 0)
	{
		g_last_exit = -1;
		ft_free_memory_envp_list(&mini->envp_list);
		ft_free_memory_matrix(mini->comand);
		file = ft_strjoin("", copy->chank);
		if (!file)
			exit (1);
		ft_free_memory_lexer_list(&mini->lexer);
		if (mini->input)
			free (mini->input);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(file, argv, mini->envp) == -1)
		{
			if (errno == EACCES)
				ft_error_exec(mini, PERMISSION_DENIED, file, argv);
			else
				ft_error_exec(mini, OTHER_ERROR, file, argv);
		}
	}
}

static t_list	*ft_found_path(t_list *envp_list, t_lexer *copy)
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
		exit (1);
	i = 0;
	while (path_matrix[i])
	{
		buffer = ft_strjoin(path_matrix[i], "/");
		if (buffer == NULL)
			exit (1);
		buffer2 = ft_strjoin(buffer, copy->chank);
		if (buffer2 == NULL)
			exit (1);
		free (path_matrix[i]);
		free (buffer);
		path_matrix[i] = buffer2;
		i++;
	}
	return (path_matrix);
}

static void	run_path(char **path, t_lexer *copy, char **argv, t_shell *mini)
{
	int			i;
	struct stat	buf;

	i = -1;
	while (path[++i])
	{
		if (stat(path[i], &buf) == 0)
		{
			g_last_exit = -1;
			ft_free_memory_envp_list(&mini->envp_list);
			ft_free_memory_matrix(mini->comand);
			ft_free_memory_lexer_list(&mini->lexer);
			if (mini->input)
				free (mini->input);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (execve(path[i], argv, mini->envp) == -1)
			{
				if (errno == EACCES)
					ft_error_exec(mini, PERMISSION_DENIED, path[i], argv);
				else
					ft_error_exec(mini, OTHER_ERROR, path[i], argv);
			}
		}
	}
}

void	ft_run_from_path(t_shell *mini, t_lexer *copy)
{
	t_list	*envp_copy;
	char	**path_matrix;
	char	**argv;

	argv = ft_create_argv(mini, copy);
	start_another_program(mini, copy, argv);
	envp_copy = ft_found_path(mini->envp_list, copy);
	path_matrix = ft_create_path_matrix(copy, envp_copy);
	run_path(path_matrix, copy, argv, mini);
}
