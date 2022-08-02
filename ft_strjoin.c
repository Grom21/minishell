/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:03:19 by etisha            #+#    #+#             */
/*   Updated: 2022/07/31 20:27:51 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	res = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < l1)
		res[i] = s1[i];
	i = 0;
	while (i < l2)
	{
		res[i + l1] = s2[i];
		i++;
	}
	res[i + l1] = '\0';
	return (res);
}
