/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:10:24 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/12 15:56:57 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->command_args[i])
	{
		if (shell->expander_flags[i] == 1)
		{
			not_expand1(shell, i);
			i++;
		}
		else if (shell->expander_flags[i] == 2)
			i++;
		else
		{
			if (ft_search(shell->command_args[i], '$') == 1)
			{
				if (expand_variable(shell, i) == -1)
				{
					free(shell->expander_flags);
					return ;
				}
			}
			i++;
		}
	}
	free(shell->expander_flags);
}

int	expand_variable(t_minishell *shell, int i)
{
	char	*after_ds;

	after_ds = get_after_dollar(shell->command_args[i]);
	if (string_comp(shell->command_args[i], "$?") == 1)
	{
		free(after_ds);
		free(shell->command_args[i]);
		shell->command_args[i] = ft_itoa(g_exit_status);
	}
	else if (check_var_true(after_ds, shell) == 0)
	{
		free(after_ds);
		g_exit_status = 127;
		free(shell->command_args[i]);
		shell->command_args[i] = ft_strdup(" ");
		return (-1);
	}
	else
		perform_variable_expansion(shell, i, after_ds);
	return (0);
}

void	perform_variable_expansion(t_minishell *shell, int i, char *after_ds)
{
	char	*temp;
	char	*before_ds;

	temp = ft_strdup(after_ds);
	free(after_ds);
	after_ds = var_value(temp, shell);
	free(temp);
	before_ds = get_before_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strjoin(before_ds, after_ds);
	free(after_ds);
	free(before_ds);
}
void	not_expand1(t_minishell *shell, int i)
{
	char	*after_ds;

	after_ds = get_after_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strdup(after_ds);
	free(after_ds);
}
