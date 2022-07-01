#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen_key(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=' )
		i++;
	return (i);
}

size_t	ft_strlen_value(const char *s)
{
	int	i;
	int y;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	y = 0;
	while (s[i] != '\0')
	{
		i++;
		y++;
	}
	return (y);
}
