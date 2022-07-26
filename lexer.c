/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:03:46 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:03:47 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_memory_lexer_list(t_lexer **lexer)
{
	t_lexer	*buffer;

	while (*lexer)
	{
		buffer = (*lexer)->next;
		if ((*lexer)->chank)
			free ((*lexer)->chank);
		free (*lexer);
		*lexer = buffer;
	}
	*lexer = NULL;
}

static void	save_inp_in_list(t_lexer **list, char *input, int start, int stop)
{
	int	i;

	i = 0;
	while (start < stop)
	{
		(*list)->chank[i] = input[start];
		i++;
		start++;
	}
	(*list)->chank[i] = '\0';
}

static t_lexer	*ft_create_elem(char *input, int start, int stop)
{
	t_lexer	*list;

	list = (t_lexer *)malloc(sizeof(t_lexer));
	if (!list)
		return (NULL);
	list->chank = NULL;
	list->chank = (char *)malloc(sizeof(char) * (stop - start + 1));
	if (!list->chank)
		return (NULL);
	save_inp_in_list(&list, input, start, stop);
	list->next = NULL;
	return (list);
}

void	ft_create_lexer(t_lexer **lexer, char *input, int start, int stop)
{
	t_lexer	*lastlist;

	lastlist = *lexer;
	if (!lastlist)
	{
		*lexer = ft_create_elem(input, start, stop);
		if (!(*lexer))
		{
			ft_free_memory_lexer_list(lexer);
			*lexer = NULL;
			return ;
		}
	}
	else
	{
		while (lastlist->next)
			lastlist = lastlist->next;
		lastlist->next = ft_create_elem(input, start, stop);
		if (!lastlist->next)
		{
			ft_free_memory_lexer_list(lexer);
			*lexer = NULL;
			return ;
		}
	}
}

void	ft_lexer(t_lexer **lexer, char	*input)
{
	int	start;
	int	stop;

	lex_run_space(lexer, input, &start, &stop);
	while (input[start] != '\0')
	{
		if (input[stop] != ' ' && input[stop] != '|' && input[stop] != '\"' \
		&& input[stop] != '\'' && input[stop] != '<' && input[stop] != '>' \
		&& input[stop] != '\0')
			ft_lexer_word(lexer, input, &start, &stop);
		if (input[stop] == ' ' && input[stop] != '\0')
			ft_lexer_spase(lexer, input, &start, &stop);
		if ((input[stop] == '|' && input[stop] != '\0'))
			ft_lexer_delim(lexer, input, &start, &stop);
		if (input[stop] == '\'' && input[stop] != '\0')
			lex_s_quotes(lexer, input, &start, &stop);
		if (input[stop] == '\"' && input[stop] != '\0')
			lex_d_quotes(lexer, input, &start, &stop);
		if ((input[stop] == '<' && input[stop] != '\0') \
		|| (input[stop] == '>' && input[stop] != '\0'))
			lexer_redir(lexer, input, &start, &stop);
	}
}
