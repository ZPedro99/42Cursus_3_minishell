/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:03:08 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/24 16:57:57 by emsoares         ###   ########.fr       */
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
	while (str[j])
	{
		temp[i] = str[j];
		i++;
		j++;
	}
	temp[i] = '\"';
	i++;
	temp[i] = '\0';
	return (temp);
}

void	get_prompt(t_minishell *shell)
{
	char	*username;
	char	*seat;
	char	*temp;
	int		i;
	int		j;

	username = getenv("USER");
	temp = getenv("SESSION_MANAGER");
	i = 0;
	while (temp[i] != '/')
		i++;
	i++;
	j = i;
	while (temp[j] != '.')
		j++;
	seat = get_prompt2(i, j, temp);
	shell->prompt = ft_strjoin(username, seat);
	free(seat);
}

char	*get_prompt2(int i, int j, char *temp)
{
	char	*seat;

	seat = malloc(sizeof(char) * (j - i) + 4);
	j = 1;
	seat[0] = '@';
	while (temp[i] != '.')
	{
		seat[j] = temp[i];
		i++;
		j++;
	}
	seat[j] = '>';
	j++;
	seat[j] = ' ';
	j++;
	seat[j] = '\0';
	return (seat);
}
