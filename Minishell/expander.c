/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:10:24 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/26 16:41:59 by jomirand         ###   ########.fr       */
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
		else if (ft_strrchr(shell->command_args[i], '"')
			|| ft_strrchr(shell->command_args[i], '\''))
			i++;
		else
		{
			if (ft_search(shell->command_args[i], '$') == 1)
				expand_variable(shell, i);
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
	else if (shell->command_args[i][1] == '\0')
		return (free(after_ds), 0);
	else if (count_dollars(shell->command_args[i]) > 1)
	{
		free(after_ds);
		expand_multiple(shell, i, 0, 0);
		shell->expander_flag = 0;
	}
	else if (check_var_true(after_ds, shell) == 0)
		return (var_false(shell, i, after_ds), -1);
	else
		perform_var_expansion(shell, i, after_ds);
	return (0);
}

void	perform_var_expansion(t_minishell *shell, int i, char *after_ds)
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
	g_exit_status = 0;
}

char	*perform_var_expansion2(t_minishell *shell, char *after_ds)
{
	char	*temp;

	temp = ft_strdup(after_ds);
	free(after_ds);
	after_ds = var_value(temp, shell);
	free(temp);
	return (after_ds);
}
