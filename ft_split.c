#include "minishell.h"

static int	ft_found_word(char const *s, char c)
{
	int	countword;
	int	i;

	if (s == NULL || (c == 0 && ft_strlen(s) == 0))
		return (0);
	countword = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			countword++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (countword);
}

void	ft_free_memory_split(char **matrix, int x)
{
	x--;
	while (x >= 0)
	{
		free(matrix[x]);
		x--;
	}
	free(matrix);
}

static char	**ft_create(char **matrix, int countword, char const *s, char c)
{
	int		i;
	int		x;
	int		lenword;

	i = 0;
	x = -1;
	while (++x < countword)
	{
		lenword = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			lenword++;
		}
		matrix[x] = (char *)malloc(sizeof(char) * (lenword + 1));
		if (matrix[x] == NULL)
		{
			ft_free_memory_split(matrix, x);
			return (NULL);
		}
		matrix[x][lenword] = '\0';
	}
	return (matrix);
}

static char	**ft_saveword(char **matrix, int countword, char const *s, char c)
{
	int	y;
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (++x < countword)
	{
		while (s[i] == c)
			i++;
		y = 0;
		while (s[i] != c && s[i] != '\0')
		{
			matrix[x][y] = s[i];
			i++;
			y++;
		}
		matrix[x][y] = '\0';
	}
	matrix[x] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		countword;

	countword = ft_found_word(s, c);
	matrix = (char **)malloc(sizeof(char *) * (countword + 1));
	if (matrix == NULL)
		return (NULL);
	matrix = ft_create(matrix, countword, s, c);
	if (matrix == NULL)
		return (NULL);
	matrix = ft_saveword(matrix, countword, s, c);
	return (matrix);
}
