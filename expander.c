/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:10:24 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/14 11:43:03 by jomirand         ###   ########.fr       */
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
		else if(ft_strrchr(shell->command_args[i], '"') || ft_strrchr(shell->command_args[i], '\''))
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
	{
		free (after_ds);
		return (0);
	}
	else if (count_dollars(shell->command_args[i]) > 1)
	{
		free(after_ds);
		expand_multiple(shell, i);
	}
	else if (check_var_true(after_ds, shell) == 0)
	{
		free(after_ds);
		g_exit_status = 127;
		free(shell->command_args[i]);
		shell->command_args[i] = ft_strdup("");
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
	g_exit_status = 0;
}
void	not_expand1(t_minishell *shell, int i)
{
	char	*after_ds;

	after_ds = get_after_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strdup(after_ds);
	free(after_ds);
}

void	expand_multiple(t_minishell *shell, int i)
{
	int		start = 0;
	int		end;
	char	*temp;
	char 	*temp2;
	char 	*return_str;
	int		x = 0;

	while (shell->command_args[i][start] != '\0')
	{
		while (shell->command_args[i][start] != '$' && shell->command_args[i][start] != '\0')
			start++;
		if(shell->command_args[i][start] != '\0')
			start++;
		end = start;
		while (shell->command_args[i][end] != '$' && shell->command_args[i][end] != '\0')
			end++;
		temp = ft_substr(shell->command_args[i], start, end - start);
		if(check_var_true(temp, shell) == 0)
		{
			temp2 = ft_strdup(return_str);
			free(return_str);
			return_str = ft_strjoin(temp2, "");
			free(temp);
			free(temp2);
		}
		else
		{
			if(x == 0)
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
		}
		start = end;
	}
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strdup(return_str);
	free(return_str);
}


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
	/* before_ds = get_before_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strjoin(before_ds, after_ds); */
	//return_str = ft_strjoin(before_ds, after_ds);
	//free(after_ds);
	//free(before_ds);
	return(after_ds);
}