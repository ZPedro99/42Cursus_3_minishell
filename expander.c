/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:10:24 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/24 12:10:12 by jomirand         ###   ########.fr       */
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

	if (check_expand_es(shell, i) == 0)
		return (0);
	if (shell->command_args[i][1] == '\0')
		return (0);
	else if (count_dollars(shell->command_args[i]) > 1)
	{
		expand_multiple(shell, i, 0, 0);
		return (0);
	}
	else if (check_var_true(after_ds, shell) == 0)
	{
		g_exit_status = 127;
		free(shell->command_args[i]);
		shell->command_args[i] = ft_strdup("");
		return (-1);
	}
	else
	{
		after_ds = get_after_dollar(shell->command_args[i]);
		perform_variable_expansion(shell, i, after_ds);
	}
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
	g_exit_status = 0;
}

void	expand_multiple(t_minishell *sh, int i, int x, int start)
{
	int		end;
	char	*temp;
	char	*temp2;
	char	*return_str;

	while (sh->command_args[i][start] != '\0')
	{
		while (sh->command_args[i][start] != '$' && sh->command_args[i][start])
			start++;
		if (sh->command_args[i][start] != '\0')
			start++;
		end = start;
		while (sh->command_args[i][end] != '$' && sh->command_args[i][end])
			end++;
		temp = ft_substr(sh->command_args[i], start, end - start);
		if (check_var_true(temp, sh) == 0)
			return_str = obtain_return_str(temp, temp2, return_str);
		else
			return_str = continue_expanding(temp, temp2, return_str, x);
		start = end;
	}
	free(sh->command_args[i]);
	sh->command_args[i] = ft_strdup(return_str);
	free(return_str);
}

char	*continue_expanding(char *temp, char *temp2, char *return_str, int x)
{
	if (x == 0)
	{
		x = 1;
		temp2 = perform_variable_expansion2(shell, temp);
		return_str = ft_strjoin(temp2, "");
		free(temp2);
	}
	else
	{
		temp2 = perform_variable_expansion2(shell, temp);
		temp = ft_strdup(return_str);
		free(return_str);
		return_str = ft_strjoin(temp, temp2);
		free(temp2);
		free(temp);
	}
	return (return_str);
}
