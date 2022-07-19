#include "minishell.h"

int	ft_pwd(void)	//think about errors!
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		write (2, "Error getcwd!\n", 14);
		return (1);		//????
	}
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	free(buf);
	g_last_exit = 0;
	return (0);
}
