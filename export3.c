/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:02:21 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 11:02:12 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_value_env(t_minishell *shell, char *str, char *name)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		name = get_var_name(str);
		temp = NULL;
	}
	else
	{
		name = get_var_name(str);
		temp = get_temp(str, i, j);
	}
	change_value_env2(shell, name, temp);
}

void	change_value_env2(t_minishell *shell, char *name, char *temp)
{
	t_list	*temp_env;

	temp_env = shell->env;
	while (!string_comp(((t_env *)(temp_env->content))->name, name))
		temp_env = temp_env->next;
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(temp);
	if (string_comp(name, "PATH="))
	{
		free_splited(shell->paths);
		shell->paths = save_paths(((t_env *)(temp_env->content))->info);
	}
	free(temp);
	free(name);
}

int	ft_check_dup3(t_minishell *shell, char *str)
{
	t_list	*head;
	char	*temp;
	char	*search;

	head = shell->exp;
	temp = ft_strjoin(str, "=");
	search = ft_strjoin("declare -x ", temp);
	free(temp);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, search))
		{
			free(search);
			return (0);
		}
		head = head->next;
	}
	free(search);
	if (ft_check_dup4(shell, str) == 0)
		return (0);
	if (ft_strchr(str, ':'))
		ft_putstr_fd("Minishell: unset : not a valid identifier", 2);
	return (1);
}

int	ft_check_dup4(t_minishell *shell, char *str)
{
	t_list	*head;
	char	*search;

	head = shell->exp;
	search = ft_strjoin("declare -x ", str);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, search))
		{
			free(search);
			return (0);
		}
		head = head->next;
	}
	free(search);
	return (1);
}

int	ft_check_exp(t_minishell *shell, char *str)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	temp2 = ft_strjoin("declare -x ", temp);
	free(temp);
	return (ft_check_exp2(shell, temp2));
}
