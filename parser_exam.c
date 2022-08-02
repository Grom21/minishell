/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:01 by etisha            #+#    #+#             */
/*   Updated: 2022/08/01 02:05:51 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*ft_exam_double_pipe(t_lexer *copy, t_shell *mini)
{
	t_lexer	*nextlist;

	while (copy->next)
	{
		if (copy->chank[0] == '|')
		{
			nextlist = copy->next;
			if (nextlist->chank[0] == ' ')
				nextlist = nextlist->next;
			if (nextlist->chank[0] == '|')
			{
				ft_print_parser_error(&mini->lexer, SYNTAX_PIPE_ERROR);
				return (NULL);
			}
		}
		copy = copy->next;
	}
	return (copy);
}

int	ft_exam_pipe_first_last_double(t_shell *mini)
{
	t_lexer	*copy;

	copy = mini->lexer;
	if (ft_strcmp(copy->chank, "|") == 0)
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_PIPE_ERROR);
		return (258);
	}
	copy = ft_exam_double_pipe(copy, mini);
	if (!copy)
		return (258);
	if (ft_strcmp(copy->chank, "|") == 0)
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_PIPE_ERROR);
		return (258);
	}
	return (0);
}

int	ft_exam_syntax_quotes(t_shell *mini)
{
	t_lexer	*copy;
	char	*chank;
	int		len;

	copy = mini->lexer;
	while (copy)
	{
		chank = copy->chank;
		len = ft_strlen(chank);
		if ((chank[0] == '\'' && len == 1) || (chank[0] == '\"' && len == 1))
		{
			ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
			return (SYNTAX_ERROR);
		}
		if ((chank[0] == '\'' && chank[len - 1] != '\'') \
		|| (chank[0] == '\"' && chank[len - 1] != '\"'))
		{
			ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
			return (SYNTAX_ERROR);
		}
		copy = copy->next;
	}
	return (0);
}

int	ft_exam_double_redirect(t_shell *mini)
{
	t_lexer	*copy;
	t_lexer	*nextlist;

	copy = mini->lexer;
	while (copy->next)
	{
		if ((copy->chank[0] == '<') || (copy->chank[0] == '>'))
		{
			nextlist = copy->next;
			if (nextlist->chank[0] == ' ')
				nextlist = nextlist->next;
			if (nextlist->chank[0] == '<' || nextlist->chank[0] == '>' \
			|| nextlist->chank[0] == '|')
			{
				ft_print_token_error(nextlist->chank, SYNTAX_TOKEN_ERROR);
				return (258);
			}
		}
		copy = copy->next;
	}
	return (0);
}

int	ft_exam_last_redirect(t_shell *mini)
{
	t_lexer	*copy;

	copy = mini->lexer;
	while (copy->next)
		copy = copy->next;
	if (copy->chank[0] == '<' || copy->chank[0] == '>')
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_REDIR_ERROR);
		return (258);
	}
	return (0);
}
