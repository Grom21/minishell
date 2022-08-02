/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:36 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:02:37 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_memory_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free (matrix[i]);
		i++;
	}
	free (matrix);
}

void	ft_free_memory_envp_list(t_list **envp_list)
{
	t_list	*buffer;

	while (*envp_list)
	{
		buffer = (*envp_list)->next;
		if ((*envp_list)->key)
			free ((*envp_list)->key);
		if ((*envp_list)->value)
			free ((*envp_list)->value);
		free (*envp_list);
		*envp_list = buffer;
	}
}
