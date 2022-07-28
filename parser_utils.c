/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:06 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 00:22:16 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_save_char(t_lexer *new, char c)
{
	char	buf[2];
	char	*str;

	buf[1] = '\0';
	buf[0] = c;
	str = ft_strjoin(new->chank, buf);
	if (str == NULL)
		return (-1);
	free (new->chank);
	new->chank = str;
	str = NULL;
	return (0);
}

int	ft_take_envp(t_lexer *new, t_lexer *old, int i, t_list *envp)
{
	t_list	*copy_envp;
	char	*str;
	int		x;

	copy_envp = envp;
	str = old->chank + i + 1;
	while (copy_envp)
	{
		if (ft_strcmp_echo(str, copy_envp->key) == 0)
		{
			x = 0;
			while (copy_envp->value[x])
			{
				if (ft_save_char(new, copy_envp->value[x]) != 0)
					return (-1);
				x++;
			}
		}
		copy_envp = copy_envp->next;
	}
	while (old->chank[i + 1] && old->chank[i + 1] != '$' \
	&& old->chank[i + 1] != '\"' && old->chank[i + 1] != ' ')
		i++;
	return (i);
}

static t_lexer	*ft_create_elem(void)
{
	t_lexer	*list;

	list = (t_lexer *)malloc(sizeof(t_lexer));
	if (!list)
		return (NULL);
	list->chank = NULL;
	list->chank = (char *)malloc(sizeof(char));
	if (!list->chank)
		return (NULL);
	list->chank[0] = '\0';
	list->next = NULL;
	return (list);
}

void	ft_parser_create(t_lexer **new)
{
	t_lexer	*lastlist;

	lastlist = *new;
	if (!lastlist)
	{
		*new = ft_create_elem();
		if (!(*new))
		{
			ft_free_memory_lexer_list(new);
			*new = NULL;
			return ;
		}
	}
	else
	{
		while (lastlist->next)
			lastlist = lastlist->next;
		lastlist->next = ft_create_elem();
		if (!lastlist->next)
		{
			ft_free_memory_lexer_list(new);
			*new = NULL;
			return ;
		}
	}
}
