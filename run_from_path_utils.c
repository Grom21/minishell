/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_from_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:35 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 03:39:23 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_exit_or_not(t_shell *mini, char *str)
{
	if (str == NULL)
	{
		ft_free_memory_lexer_list(&mini->lexer);
		ft_free_memory_envp_list(&mini->envp_list);
		ft_free_memory_matrix(mini->envp);
		ft_free_memory_matrix(mini->comand);
		if (mini->input)
			free (mini->input);
		exit (1);
	}
}

char	**ft_create_argv(t_shell *mini, t_lexer *copy)
{
	char		**matrix;
	char		*buffer;
	char		*buffer2;

	if (copy->next && copy->next->chank[0] != '|' \
	&& copy->next->chank[0] != '<' && copy->next->chank[0] != '>')
	{
		buffer = ft_strjoin(copy->chank, " ");
		ft_check_exit_or_not(mini, buffer);
		buffer2 = ft_strjoin(buffer, copy->next->chank);
		ft_check_exit_or_not(mini, buffer2);
		free (buffer);
		matrix = ft_split(buffer2, ' ');
		if (matrix == NULL)
			exit (1);
		free (buffer2);
	}
	else
	{
		matrix = ft_split(copy->chank, ' ');
		if (matrix == NULL)
			exit (1);
	}
	return (matrix);
}

void	ft_error_stat(t_shell *mini, int exeption, char *str, char **argv)
{
	if (exeption == NOT_A_DIRECTORY)
	{
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": Not a directory\n", 18);
		ft_free_memory_envp_list(&mini->envp_list);
		ft_free_memory_matrix(mini->comand);
		ft_free_memory_lexer_list(&mini->lexer);
		ft_free_memory_matrix(mini->envp);
		if (mini->input)
			free (mini->input);
		ft_free_memory_matrix(argv);
		exit (126);
	}
}

void	ft_error_exec(t_shell *mini, int exeption, char *str, char **argv)
{
	if (exeption == PERMISSION_DENIED)
	{
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 21);
		ft_free_memory_matrix(argv);
		ft_free_memory_matrix(mini->envp);
		free(str);
		exit (126);
	}
	if (exeption == OTHER_ERROR)
	{
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": error\n", 8);
		ft_free_memory_matrix(argv);
		ft_free_memory_matrix(mini->envp);
		free(str);
		exit (1);
	}
}
