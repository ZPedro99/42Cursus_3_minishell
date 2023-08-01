/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:35:53 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 10:29:49 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exp_input(char *s)
{
	char	*temp;
	char	*temp1;

	temp = get_var_name(s);
	if (ft_search(temp, '=') == 1)
	{
		temp1 = ft_strdup(temp);
		free(temp);
		temp = ft_strtrim(temp1, "=");
		free(temp1);
	}
	if ((ft_isalpha(temp[0]) == 0) && temp[0] != '_')
	{
		free(temp);
		return (0);
	}
	if (check_exp_input2(temp) == 0)
		return (0);
	return (1);
}

int	check_exp_input2(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if ((ft_isalnum(temp[i]) == 1) || temp[i] == '_' )
			i++;
		else
		{
			free(temp);
			return (0);
		}
	}
	free(temp);
	return (1);
}

char	*quote_remover_exp(char *s)
{
	int		i;
	char	*new;
	char	temp;

	i = 0;
	while (s[i] != '\'' && s[i] != '"' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		new = ft_strdup(s);
		return (new);
	}
	temp = s[i];
	new = quote_remover_exp2(s, temp);
	return (new);
}

char	*quote_remover_exp2(char *s, char temp)
{
	int		i;
	char	*new;
	int		j;

	j = 0;
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) - counting_quote(s, temp) + 1));
	while (s[i] != '\0')
	{
		if (s[i] == temp)
			i++;
		else
		{
			new[j] = s[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}
