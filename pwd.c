/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:20 by etisha            #+#    #+#             */
/*   Updated: 2022/07/31 20:31:52 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		write (2, "Error getcwd!\n", 14);
		return (1);
	}
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	free(buf);
	g_last_exit = 0;
	return (0);
}
