/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:50:41 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/14 18:07:06 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*posnum(char *str, long long n, int len)
{
	long	x;

	len--;
	x = n;
	while (len >= 0)
	{
		str[len] = x % 10 + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static char	*negnum(char *str, long long n, int len)
{
	long	x;

	x = n;
	str[0] = '-';
	len--;
	x = x * (-1);
	while (len > 0)
	{
		str[len] = (x % 10) + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static int	int_len(long long n)
{
	int		i;
	long	x;

	x = n;
	i = 0;
	if (x <= 0)
	{
		x = x *(-1);
		i++;
	}
	while (x > 0)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long long n)
{
	char	*str;
	int		len;

	len = int_len(n);
	str = (char *) malloc (sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str = negnum(str, n, len);
	}
	else if (n == 0)
		str[0] = '0';
	else
		str = posnum(str, n, len);
	return (str);
}
