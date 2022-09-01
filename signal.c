/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:04:49 by etisha            #+#    #+#             */
/*   Updated: 2022/08/04 15:47:02 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_last_exit == -1)
		{
			write (2, "\n", 1);
		}
		else if (g_last_exit == -2)
		{
			write (2, "\n", 1);
			exit(1);
		}
		else
		{
			if (g_last_exit == -3)
				rl_on_new_line();
			else
			{
				ioctl(STDIN_FILENO, TIOCSTI, "\n");
				rl_replace_line("", 0);
				rl_on_new_line();
			}
			g_last_exit = 1;
		}
	}
}

void	ft_mini_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
