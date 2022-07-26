/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:23 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:02:24 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exam_void(t_lexer *lexer, t_list *envp_list)
{
	t_lexer	*lexer_copy;
	t_list	*envp_copy;

	envp_copy = envp_list;
	lexer_copy = lexer->next;
	if (!lexer_copy || lexer_copy->chank[0] == '|' \
	|| lexer_copy->chank[0] == '<' || lexer_copy->chank[0] == '>')
	{
		while (envp_copy)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(envp_copy->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(envp_copy->value, 1);
			ft_putchar_fd('\n', 1);
			envp_copy = envp_copy->next;
		}
		return (1);
	}
	if (lexer_copy && lexer_copy->chank[0] == '_' \
	&& lexer_copy->chank[1] == '=')
		return (1);
	return (0);
}

int	ft_exam_export_key(char *str, char *key)
{
	int	i;

	i = 0;
	if ((ft_isalpha(key[i]) != 1) && key[i] != '_')
	{
		free (key);
		return (ft_print_export_error(str));
	}
	i++;
	while (key[i])
	{
		if (((ft_isdigit(key[i]) == 0) && (ft_isalpha(key[i]) == 0)) \
		&& key[i] != '_')
		{
			free (key);
			return (ft_print_export_error(str));
		}
		i++;
	}
	return (0);
}
