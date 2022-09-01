/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:02 by etisha            #+#    #+#             */
/*   Updated: 2022/08/04 17:07:30 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_found_redirect_in_command(t_lexer *lexer)
{
	t_lexer	*copy;

	copy = lexer;
	while (copy && copy->chank[0] != '|')
	{
		if (copy->chank[0] == '<' || copy->chank[0] == '>')
			return (1);
		copy = copy->next;
	}
	return (0);
}

int	found_heredoc(t_lexer *lexer)
{
	t_lexer	*copy;

	copy = lexer;
	while (copy && copy->chank[0] != '|')
	{
		if (copy->chank[0] == '<' && copy->chank[1] == '<')
			return (-3);
		copy = copy->next;
	}
	return (g_last_exit);
}

void	ft_exit_with_redir(t_shell *mini, t_lexer *copy, int count, int i)
{
	int	result;

	if (count == -1 && copy && ft_strcmp("exit", copy->chank) == 0 \
	&& ft_found_redirect_in_command(copy) != 0)
	{
		ft_redirect(mini, copy, i, count);
		result = ft_found_in_castom(mini, copy);
		if (result != -1)
			exit (result);
	}
}

int	ft_find_shell(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->chank[i] != '\0')
		i++;
	while (lexer->chank[i] != '/' && i != 0)
		i--;
	if (lexer->chank[i] == '/')
		i++;
	if (ft_strcmp(&(lexer->chank[i]), "minishell") == 0 || \
	ft_strcmp(&(lexer->chank[i]), "bash") == 0 || \
	ft_strcmp(&(lexer->chank[i]), "zsh") == 0)
		return (1);
	return (0);
}

void	ft_cut_cut(t_lexer *lexer)
{
	int		i;
	t_lexer	*copy;

	copy = lexer->next;
	if (copy && copy->chank[0] != '|' \
	&& copy->chank[0] != '>' && copy->chank[0] != '<')
	{
		i = 0;
		while (copy->chank[i] != '\0')
			i++;
		if (i != 0 && copy->chank[i - 1] == ' ')
			copy->chank[i - 1] = '\0';
	}
}
