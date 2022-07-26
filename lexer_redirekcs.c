/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirekcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:03:37 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:03:37 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_run_space(t_lexer **lexer, char *input, int *start, int *stop)
{
	*start = 0;
	*stop = 0;
	while (input[(*start)] == ' ')
		(*start)++;
	*stop = *start;
	if (input[(*start)] == '\0')
		ft_create_lexer(lexer, input, *start, *stop);
}

void	lexer_redir(t_lexer **lexer, char *input, int *start, int *stop)
{
	(*stop)++;
	if ((input[(*stop)] == '<' && input[(*stop) - 1] == '<') \
	|| (input[(*stop)] == '>' && input[(*stop) - 1] == '>'))
		(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}
