/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:03:42 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:03:42 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer_word(t_lexer **lexer, char *input, int *start, int *stop)
{
	while (input[(*stop)] != ' ' && input[(*stop)] != '|' \
	&& input[(*stop)] != '\"' && input[(*stop)] != '\'' \
	&& input[(*stop)] != '<' && input[(*stop)] != '>' \
	&& input[(*stop)] != '\0')
		(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}

void	ft_lexer_spase(t_lexer **lexer, char *input, int *start, int *stop)
{
	int	i;

	(*stop)++;
	i = *stop;
	while (input[i] == ' ')
		i++;
	if (input[i] != '\0')
		ft_create_lexer(lexer, input, *start, *stop);
	while (input[(*stop)] == ' ')
		(*stop)++;
	*start = *stop;
}

void	ft_lexer_delim(t_lexer **lexer, char *input, int *start, int *stop)
{
	(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}

void	lex_s_quotes(t_lexer **lexer, char *input, int *start, int *stop)
{
	(*stop)++;
	while (input[(*stop)] != '\'' && input[(*stop)] != '\0')
		(*stop)++;
	if (input[(*stop)] == '\'')
		(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}

void	lex_d_quotes(t_lexer **lexer, char *input, int *start, int *stop)
{
	(*stop)++;
	while (input[(*stop)] != '\"' && input[(*stop)] != '\0')
			(*stop)++;
	if (input[(*stop)] == '\"')
		(*stop)++;
	ft_create_lexer(lexer, input, *start, *stop);
	*start = *stop;
}
