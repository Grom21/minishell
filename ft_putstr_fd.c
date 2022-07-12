#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

// void	ft_putnbr_fd(int n, int fd)
// {
// 	char	c;

// 	if (n == -2147483648)
// 	{
// 		write (fd, "-2147483648", 11);
// 		return ;
// 	}
// 	if (n < 0)
// 	{
// 		write (fd, "-", 1);
// 		n = -n;
// 	}
// 	if (n < 10)
// 	{
// 		c = n + '0';
// 		write (fd, &c, 1);
// 	}
// 	else
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putnbr_fd(n % 10, fd);
// 	}
// }
