/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:35:58 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 11:17:21 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_minishell *shell)
{
	int		i;
	int		count;

	count = ft_word_count(shell->command_args);
	i = 0;
	while (++i <= count)
	{
		while (shell->command_args[i])
		{
			if (ft_strrchr("\"\'", shell->command_args[i][0]))
				return (ft_putstr_fd("bash: unset: not valid identifier\n", 2));
			if (ft_check_dup3(shell, shell->command_args[i]) == 1)
				break ;
			if (only_exp(shell->command_args[i], shell) == 1)
				unset_only_exp(shell, shell->exp, i);
			else
			{
				unset_env(shell, shell->env, i);
				unset_exp(shell, shell->exp, i);
			}
			i++;
		}
	}
	return ;
}

int	only_exp(char *str, t_minishell *shell)
{
	char	*str_adjusted;
	t_list	*head;

	head = shell->exp;
	str_adjusted = ft_strjoin("declare -x ", str);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, str_adjusted))
		{
			free(str_adjusted);
			return (1);
		}
		head = head->next;
	}
	free(str_adjusted);
	return (0);
}

void	unset_env(t_minishell *shell, t_list *temp, int i)
{
	char	*var_name_adjust;
	t_list	*previous;

	previous = 0;
	var_name_adjust = adjust_name_env(shell->command_args[i]);
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
}

void	unset_exp(t_minishell *shell, t_list *temp, int i)
{
	char	*var_name_adjust;
	t_list	*previous;

	previous = 0;
	var_name_adjust = adjust_name_exp(shell->command_args[i]);
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
}

void	unset_only_exp(t_minishell *shell, t_list *temp, int i)
{
	char	*var_name_adjust;
	t_list	*previous;

	previous = 0;
	var_name_adjust = ft_strjoin("declare -x ", shell->command_args[i]);
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
}
