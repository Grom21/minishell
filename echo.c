/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:01:24 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 02:47:08 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_flag(t_lexer *lexer, int *i)
{
	t_lexer	*copy;
	int		flag_n;

	flag_n = 0;
	copy = lexer->next;
	if (copy && copy->chank[0] == '-' && copy->chank[1] == 'n' \
	&& (copy->chank[2] == ' ' || copy->chank[2] == '\0'))
	{
		flag_n = 1;
		if (copy->chank[2] == ' ')
			*i = 3;
		else
			*i = 2;
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
		if (copy->chank[i] == '$' && copy->chank[i + 1] != '$' \
		&& copy->chank[i + 1] != ' ' && copy->chank[i + 1] != '\0')
			i++;
		else
			ft_putchar_fd(copy->chank[i++], 1);
	}
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	g_last_exit = 0;
	return (0);
}
