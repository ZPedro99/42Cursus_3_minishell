/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:03:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/05 11:07:46 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;

	a = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[a] = 0;
		return (str);
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (a < len)
	{
		str[a] = s[start + a];
		a++;
	}
		str[a] = '\0';
	return (str);
}

//char	*ft_substr(char const *str, unsigned int start, size_t len)
//
//{
//	unsigned int	i;
//	char			*memall;
//
//	i = 0;
//	if (!str || !len || start >= ft_strlen((char *)str))
//	{
//		memall = malloc(1 * sizeof(char));
//		memall[0] = '\0';
//		return (memall);
//	}
//	memall = malloc((len + 1) * sizeof(char));
//	if (memall == NULL)
//		return (NULL);
//	while (i < len)
//	{
//		memall[i] = str[start];
//		start++;
//		i++;
//	}
//	memall[i] = '\0';
//	return (memall);
//}

/* #include <stdio.h>

int	main()

{
	char	str[] = "      nao gosto de rap      ";

	printf("%s\n", ft_substr(str, 6, 3));
	return(0);
} */
