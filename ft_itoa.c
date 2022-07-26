/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:02:53 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:02:54 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_intlen(int number)
{
	int	len;

	len = 0;
	if (number == 0)
		len++;
	while (number != 0)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

static char	*ft_get_memory(int len, int n)
{
	char	*result;

	if (n < 0)
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	return (result);
}

static char	*ft_min_int_to_char(char *result, int number, int len)
{
	int	i;

	i = 0;
	result[0] = '-';
	result[1] = '2';
	number = 147483648;
	i = i + 2;
	while (number != 0)
	{
		result[len] = (number % 10) + '0';
		number = number / 10;
		len--;
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*ft_int_to_char(char *result, int number, int len)
{
	int	i;

	i = 0;
	if (number < 0)
	{
		result[0] = '-';
		number = -number;
		i++;
	}
	else
		len--;
	while (number != 0)
	{
		result[len] = (number % 10) + '0';
		number = number / 10;
		len--;
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = ft_intlen(n);
	result = ft_get_memory(len, n);
	if (result == NULL)
		return (NULL);
	if (n == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	if (n == -2147483648)
	{
		result = ft_min_int_to_char(result, n, len);
		return (result);
	}
	result = ft_int_to_char(result, n, len);
	return (result);
}
