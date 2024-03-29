/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_from_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:44 by etisha            #+#    #+#             */
/*   Updated: 2022/08/04 17:07:02 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_prog(t_shell *mini, t_lexer *copy, char **argv, char *file)
{
	struct stat	buf;

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
		ft_mini_signal();
		ft_default_term(mini);
		if (execve(file, argv, mini->envp) == -1)
		{
			if (errno == EACCES)
				ft_error_exec(mini, PERMISSION_DENIED, file, argv);
			else
				ft_error_exec(mini, OTHER_ERROR, file, argv);
		}
	}
	if (errno == ENOTDIR)
		ft_error_stat(mini, NOT_A_DIRECTORY, copy->chank, argv);
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

static void	run_path(char **path, char **argv, t_shell *mini)
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
			ft_mini_signal();
			ft_default_term(mini);
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

	ft_cut_cut(copy);
	argv = ft_create_argv(mini, copy);
	if ((copy->chank[0] == '.' && copy->chank[1] == '/') \
	|| copy->chank[0] == '/')
		start_prog(mini, copy, argv, NULL);
	envp_copy = ft_found_path(mini->envp_list, copy);
	path_matrix = ft_create_path_matrix(copy, envp_copy);
	run_path(path_matrix, argv, mini);
}
