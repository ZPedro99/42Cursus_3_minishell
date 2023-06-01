/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:35:58 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/01 11:53:20 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_minishell *shell)
{
	int		i;

	i = 1;
	while (shell->command_splited[i])
	{
		unset_env(shell, shell->env);
		unset_exp(shell, shell->exp);
		i++;
	}
}

char	*adjust_name_env(char *str)
{
	char	*str_adjusted;

	str_adjusted = ft_strjoin(str, "=");
	return (str_adjusted);
}

char	*adjust_name_exp(char *str)
{
	char	*str_adjusted_temp;
	char	*final_str;

	str_adjusted_temp = ft_strjoin("declare -x ", str);
	final_str = malloc(sizeof(char) * (ft_strlen(str_adjusted_temp) + 2));
	final_str = ft_strjoin(str_adjusted_temp, "=");
	free(str_adjusted_temp);
	return (final_str);
}

void	unset_env(t_minishell *shell, t_list *temp)
{
	char	*var_name_adjust;
	int		node_num;
	int		reaching_node;
	int		i;

	node_num = 0;
	reaching_node = 0;
	i = 1;
	var_name_adjust = adjust_name_env(shell->command_splited[i]);
	while (!string_comp(((t_env *)(temp->content))->name, var_name_adjust))
	{
		temp = temp->next;
		node_num++;
	}
	temp = shell->env;
	while (reaching_node < node_num - 1)
	{
		reaching_node++;
		temp = temp->next;
	}
	free(((t_env *)(temp->next->content))->name);
	free(((t_env *)(temp->next->content))->info);
	temp->next = temp->next->next;
	//free(((t_env *)(temp->content)));
	free(var_name_adjust);
}

void	unset_exp(t_minishell *shell, t_list *temp)
{
	char	*var_name_adjust;
	int		node_num;
	int		reaching_node;
	int		i;

	node_num = 0;
	reaching_node = 0;
	i = 1;
	var_name_adjust = adjust_name_exp(shell->command_splited[i]);
	while (!string_comp(((t_env *)(temp->content))->name, var_name_adjust))
	{
		temp = temp->next;
		node_num++;
	}
	temp = shell->exp;
	while (reaching_node < node_num - 1)
	{
		reaching_node++;
		temp = temp->next;
	}
	free(((t_env *)(temp->next->content))->name);
	free(((t_env *)(temp->next->content))->info);
	//free(((t_env *)(temp->content)));
	temp->next = temp->next->next;
	free(var_name_adjust);
}