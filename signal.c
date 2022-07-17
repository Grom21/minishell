#include "minishell.h"

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_last_exit == -1)
		{
			write (2, "^C\n", 3);
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
