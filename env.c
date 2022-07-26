/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:01:29 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:01:30 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *envp_list)
{
	t_list	*copy_envp;

	copy_envp = envp_list;
	while (copy_envp)
	{
		ft_putstr_fd(copy_envp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(copy_envp->value, 1);
		ft_putchar_fd('\n', 1);
		copy_envp = copy_envp->next;
	}
	return (0);
}
