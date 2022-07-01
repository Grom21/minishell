#include "minishell.h"

// static void	ft_bzero(void *s, size_t n)
// {
// 	size_t	i;
// 	char	*str;

// 	str = s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		str[i] = '\0';
// 		i++;
// 	}
// }

// static void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*s;

// 	s = (void *)malloc(size * count);
// 	if (s == NULL)
// 		return (NULL);
// 	ft_bzero(s, (count * size));
// 	return (s);
// }

// static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t		freesizedst;
// 	int			z;
// 	int			x;
// 	int			lendst;

// 	if (dstsize == 0)
// 		return (ft_strlen(src));
// 	if (dstsize < ft_strlen(dst))
// 		return (ft_strlen(src) + dstsize);
// 	lendst = ft_strlen(dst);
// 	freesizedst = dstsize - lendst;
// 	z = 0;
// 	while (dst[z] != '\0')
// 		z++;
// 	x = 0;
// 	while (freesizedst > 1 && src[x] != '\0')
// 	{
// 		dst[z] = src[x];
// 		freesizedst--;
// 		z++;
// 		x++;
// 	}
// 	dst[z] = '\0';
// 	return (lendst + ft_strlen(src));
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dstsize == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	i = 0;
	while (i < dstsize - 1 && s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	i = ft_strlen(src);
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	char		*res;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(res = (char *)malloc((l1 + l2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < l1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		res[i + l1] = s2[i];
		i++;
	}
	res[i + l1] = '\0';
	return (res);
}
