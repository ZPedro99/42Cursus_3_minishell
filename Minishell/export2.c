/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/24 11:31:54 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_struct(t_minishell *shell, char *str)
{
	char	*temp;
	int		i;
	int		size;

	i = -1;
	size = 1;
	while (str[++i] != '=')
		size++;
	temp = ft_substr(str, 0, size);
	if (string_comp(temp, "PATH=") == 0)
	{
		free(temp);
		return ;
	}
	else
	{
		free(temp);
		temp = ft_substr(str, size, (ft_strlen(str) - size));
		free_splited(shell->paths);
		shell->paths = ft_split(temp, ':');
		free(temp);
	}
	return ;
}

int	ft_check_dup(t_minishell *shell, char *str)
{
	char	*temp;
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = '=';
	j++;
	temp[j] = '\0';
	name = ft_strjoin("declare -x ", temp);
	free(temp);
	return (ft_check_dup2(shell, str, name));
}

int	ft_check_dup2(t_minishell *shell, char *str, char *name)
{
	t_list	*head;

	head = shell->exp;
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, name))
		{
			change_value_exp(shell, str, name);
			change_value_env(shell, str, name);
			return (0);
		}
		head = head->next;
	}
	free(name);
	return (1);
}

void	change_value_exp(t_minishell *shell, char *str, char *exp_name)
{
	char		*exp_value;
	char		*temp;
	t_list		*temp_exp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		temp = NULL;
	else
		temp = get_temp(str, i, j);
	exp_value = ft_strjoin("\"", temp);
	free(temp);
	temp = ft_strjoin(exp_value, "\"");
	temp_exp = shell->exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name, exp_name))
		temp_exp = temp_exp->next;
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = ft_strdup(temp);
	free(temp);
	free(exp_name);
	free(exp_value);
}

char	*get_temp(char *str, int i, int j)
{
	char	*temp;
	int		size;

	size = ft_strlen(str);
	temp = malloc(sizeof(char) * (size - i + 1));
	i++;
	while (str[i] != '\0')
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}
