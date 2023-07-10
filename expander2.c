/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:17:01 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/10 17:44:27 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_after_dollar(char *str)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	while (str[i] != '$')
		i++;
	trimmed = malloc(sizeof(char) * ((ft_strlen(str) - i + 1)));
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		trimmed[j] = str[i];
		i++;
		j++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

char	*get_before_dollar(char *str)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (str[i] != '$')
		i++;
	trimmed = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '$')
	{
		trimmed[i] = str[i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

int	check_var_true(char *str, t_minishell *shell)
{
	t_list	*head;
	char	*temp;

	temp = ft_strjoin(str, "=");
	head = shell->env;
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, temp) == 1)
		{
			free(temp);
			return (1);
		}
		head = head->next;
	}
	free(temp);
	return (0);
}

char	*var_value(char *str, t_minishell *shell)
{
	t_list	*head;
	char	*value;
	char	*temp;

	temp = ft_strjoin(str, "=");
	head = shell->env;
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, temp) == 1)
		{
			free(temp);
			value = ft_strdup(((t_env *)(head->content))->info);
			return (value);
		}
		head = head->next;
	}
	free(temp);
	return (0);
}
