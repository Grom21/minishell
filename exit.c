/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:17 by etisha            #+#    #+#             */
/*   Updated: 2022/08/04 16:45:50 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_signal(t_shell *mini)
{
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	if (mini->input)
		free (mini->input);
	write (2, "\033[0F", 4);
	write(2, "minishell$ exit\n", 16);
	ft_default_term(mini);
	exit (g_last_exit);
}

static void	ft_exit_error(t_shell *mini, t_lexer *copy)
{
	int	i;
	int	pipe;

	pipe = ft_found_command_with_pipe(mini->lexer);
	if (pipe == -1)
		write (2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	i = 0;
	while (copy->chank[i] != '\0' && copy->chank[i] != ' ')
		write(2, &copy->chank[i++], 1);
	write (2, ": numeric argument required\n", 28);
	ft_free_memory_lexer_list(&mini->lexer);
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	if (mini->input)
		free (mini->input);
	ft_default_term(mini);
	exit (255);
}

static int	ft_exam_long(char *str)
{
	long long int	i;

	i = ft_strlen(str);
	if (str[0] == '-' && i < 20)
		return (0);
	else if (i < 19)
		return (0);
	if ((str[0] == '-' && i > 20) || (str[0] != '-' && i > 19))
		return (1);
	i = ft_atoi_long(str);
	if (str[0] == '-' && i > 0)
		return (1);
	else if (str[0] != '-' && i < 0)
		return (1);
	return (0);
}

static int	ft_exam_exit(t_shell *mini, t_lexer *copy)
{
	int	i;

	if (copy->chank[0] == '\0' || copy->chank[0] == ' ')
		ft_exit_error(mini, copy);
	i = 0;
	while (copy->chank[i] && copy->chank[i] != ' ')
	{
		if ((i != 0 && ft_isdigit(copy->chank[i]) == 0) \
		|| (i == 0 && copy->chank[i] != '-' && copy->chank[i] != '+' \
		&& ft_isdigit(copy->chank[i]) == 0) || ft_exam_long(copy->chank) != 0)
			ft_exit_error(mini, copy);
		i++;
	}
	if (copy->chank[i] != '\0')
	{
		if (ft_found_command_with_pipe(mini->lexer) == -1)
			write (2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	else
		exit (ft_atoi(copy->chank));
}

int	ft_exit(t_shell *mini, t_lexer *lexer)
{
	t_lexer	*copy;
	int		result;
	int		pipe;

	copy = lexer->next;
	if (copy && copy->chank[0] != '|' \
	&& copy->chank[0] != '<' && copy->chank[0] != '>')
	{
		result = ft_exam_exit(mini, copy);
		if (result != 0)
			return (result);
	}
	pipe = ft_found_command_with_pipe(mini->lexer);
	if (pipe == -1)
		write (2, "exit\n", 5);
	ft_free_memory_lexer_list(&mini->lexer);
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	if (mini->input)
		free (mini->input);
	ft_default_term(mini);
	if (pipe == -1)
		exit (g_last_exit);
	exit (EXIT_SUCCESS);
}
