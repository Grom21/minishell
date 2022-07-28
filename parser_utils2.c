/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:11 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 02:27:18 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_single_quotes(t_lexer *new_copy, t_lexer *old_copy, int i)
{
	char	buf[2];
	char	*str;

	buf[1] = '\0';
	while (old_copy->chank[++i] != '\'')
	{
		buf[0] = old_copy->chank[i];
		str = ft_strjoin(new_copy->chank, buf);
		if (str == NULL)
			return (-1);
		free (new_copy->chank);
		new_copy->chank = str;
		str = NULL;
	}
	i++;
	return (i);
}

static int	ft_exit_status(t_lexer *new, t_lexer *old, int i)
{
	char	*exit_status;
	int		x;

	if (old->chank[i] == '$' && old->chank[i + 1] == '?')
	{
		exit_status = ft_itoa(g_last_exit);
		if (exit_status == NULL)
			return (-1);
		x = 0;
		while (exit_status[x])
		{
			if (ft_save_char(new, exit_status[x]) != 0)
			{
				free (exit_status);
				return (-1);
			}
			x++;
		}
		i++;
		i++;
		free (exit_status);
	}
	return (i);
}

static int	ft_word(t_lexer *new, t_lexer *old, int i, t_list *envp)
{
	char	*s;

	s = old->chank;
	while (s[i] != '\0')
	{
		i = ft_exit_status(new, old, i);
		if (i < 0)
			return (-1);
		if (s[i] == '$' && s[i + 1] != '?' && s[i + 1] != ' ' \
		&& s[i + 1] != '$' && s[i + 1] != '\0')
		{
			i = ft_take_envp(new, old, i, envp) + 1;
			if (i < 0)
				return (-1);
		}
		if ((s[i] == '$' && (s[i + 1] == '$' || s[i + 1] == '\0' \
		|| s[i + 1] == ' ')) || (s[i] != '\0' && s[i] != '$'))
		{
			if (ft_save_char(new, old->chank[i]) != 0)
				return (-1);
			i++;
		}
	}
	return (i);
}

static int	ft_double_quotes(t_lexer *new, t_lexer *old, int i, t_list *envp)
{
	char	*s;

	s = old->chank;
	i++;
	while (s[i] != '\"')
	{
		i = ft_exit_status(new, old, i);
		if (i < 0)
			return (-1);
		if (s[i] == '$' && s[i + 1] != '?' && s[i + 1] != ' ' \
		&& s[i + 1] != '$' && s[i + 1] != '\"')
		{
			i = ft_take_envp(new, old, i, envp) + 1;
			if (i < 0)
				return (-1);
		}
		if ((s[i] == '$' && (s[i + 1] == '$' || s[i + 1] == '\"' \
		|| s[i + 1] == ' ')) || (s[i] != '\"' && s[i] != '$'))
		{
			if (ft_save_char(new, old->chank[i]) != 0)
				return (-1);
			i++;
		}
	}
	return (i + 1);
}

int	pars_save(t_lexer *new_copy, t_lexer *old_copy, t_list *envp_list)
{
	int	i;

	i = 0;
	while (old_copy->chank[i])
	{
		if (old_copy->chank[i] == '\'')
		{
			i = ft_single_quotes(new_copy, old_copy, i);
			if (i < 0)
				return (-1);
		}
		else if (old_copy->chank[i] == '\"')
		{
			i = ft_double_quotes(new_copy, old_copy, i, envp_list);
			if (i < 0)
				return (-1);
		}
		else
		{
			i = ft_word(new_copy, old_copy, i, envp_list);
			if (i < 0)
				return (-1);
		}
	}
	return (0);
}
