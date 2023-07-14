/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:28:10 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/14 18:34:19 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dollars(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*perform_variable_expansion2(t_minishell *shell, char *after_ds)
{
	char	*temp;

	temp = ft_strdup(after_ds);
	free(after_ds);
	after_ds = var_value(temp, shell);
	free(temp);
	return (after_ds);
}

void	not_expand1(t_minishell *shell, int i)
{
	char	*after_ds;

	after_ds = get_after_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strdup(after_ds);
	free(after_ds);
}

int	check_expand_es(t_minishell *shell, int i)
{
	if (string_comp(shell->command_args[i], "$?") == 1)
	{
		free(shell->command_args[i]);
		shell->command_args[i] = ft_itoa(g_exit_status);
		return (0);
	}
	return (1);
}
