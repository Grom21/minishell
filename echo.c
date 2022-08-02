/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:01:24 by etisha            #+#    #+#             */
/*   Updated: 2022/07/31 20:26:42 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_flag(t_lexer *lexer, int *i)
{
	t_lexer	*copy;
	int		flag_n;

	flag_n = 0;
	copy = lexer->next;
	while (copy && copy->chank[*i] == '-' && copy->chank[*i + 1] == 'n' \
	&& (copy->chank[*i + 2] == ' ' || copy->chank[*i + 2] == '\0'))
	{
		flag_n = 1;
		if (copy->chank[2] == ' ')
			*i = *i + 3;
		else
			*i = *i + 2;
	}
	return (flag_n);
}

int	ft_echo(t_lexer *lexer)
{
	t_lexer	*copy;
	int		flag_n;
	int		i;

	copy = lexer->next;
	i = 0;
	flag_n = ft_echo_flag(lexer, &i);
	while (copy && copy->chank[i] && copy->chank[0] != '<' \
	&& copy->chank[0] != '>')
	{
		if (copy->chank[i] == ' ' && copy->chank[i + 1] == '\0')
			i++;
		else
			ft_putchar_fd(copy->chank[i++], 1);
	}
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	g_last_exit = 0;
	return (0);
}
