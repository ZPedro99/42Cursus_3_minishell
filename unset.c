/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:35:58 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/02 11:04:26 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_minishell *shell)
{
	int		i;

	i = 1;
	while (shell->command_splited[i])
	{
		unset_env(shell, shell->env, i);
		unset_exp(shell, shell->exp, i);
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
	final_str = ft_strjoin(str_adjusted_temp, "=");
	free(str_adjusted_temp);
	return (final_str);
}

void	unset_env(t_minishell *shell, t_list *temp, int i)
{
	char	*var_name_adjust;
	t_list	*previous;
	/* int		i;

	i = 1; */
	previous = 0;
	var_name_adjust = adjust_name_env(shell->command_splited[i]);
	while (!string_comp(((t_env *)(temp->content))->name, var_name_adjust))
	{
		previous = temp;
		temp = temp->next;
	}
	previous->next = temp->next;
	free(((t_env *)(temp->content))->name);
	free(((t_env *)(temp->content))->info);
	free(((t_env *)(temp->content)));
	free(temp);
	free(var_name_adjust);
	//temp->next = temp->next->next;
}

void	unset_exp(t_minishell *shell, t_list *temp, int i)
{
	char	*var_name_adjust;
	t_list	*previous;
	/* int		i;

	i = 1; */
	previous = 0;
	var_name_adjust = adjust_name_exp(shell->command_splited[i]);
	while (!string_comp(((t_env *)(temp->content))->name, var_name_adjust))
	{
		previous = temp;
		temp = temp->next;
	}
	previous->next = temp->next;
	free(((t_env *)(temp->content))->name);
	free(((t_env *)(temp->content))->info);
	free(((t_env *)(temp->content)));
	free(temp);
	free(var_name_adjust);
	//temp->next = temp->next->next;
}