/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:03:08 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/06 09:34:45 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_comp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (1);
	return (0);
}

int	len_compare(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	if (ft_strlen(s2) > ft_strlen(s1))
		return (ft_strlen(s2));
	return (ft_strlen(s1));
}

char	*join_quotes(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 3));
	temp[0] = '\"';
	while(str[j])
	{
		temp[i] = str[j];
		i++;
		j++;
	}
	temp[i] = '\"';
	i++;
	temp[i] = '\0';
	return(temp);
}