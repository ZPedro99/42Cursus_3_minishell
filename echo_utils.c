/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:07:45 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/13 21:55:43 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordcount(char *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wordcount++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wordcount);
}

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] == '-')
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	counting_quote(char *str, char c)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == c)
			quote_count++;
		i++;
	}
	return (quote_count);
}

int	check_dollar_sign(char *str, t_minishell *shell)
{
	char		*name;
	t_list		*temp;

	name = get_dup_str(str);
	temp = shell->env;
	while (temp != NULL)
	{
		if (string_comp(((t_env *)(temp->content))->name, name))
		{
			printf("%s", ((t_env *)(temp->content))->info);
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	if (!temp)
	{
		free(name);
		return (0);
	}
	free(name);
	return (0);
}

char	*get_dup_str(char *str)
{
	char	*name;
	int		len;
	int		j;

	j = 0;
	name = malloc(sizeof(char) * ft_strlen(str) + 1);
	len = ft_strlen(str);
	while (j < (len - 1))
	{
		name[j] = str[j + 1];
		j++;
	}
	name[j] = '=';
	j++;
	name[j] = '\0';
	return (name);
}
