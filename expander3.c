/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:07:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 17:35:07 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	not_expand1(t_minishell *shell, int i)
{
	char	*after_ds;

	after_ds = get_after_dollar(shell->command_args[i]);
	free(shell->command_args[i]);
	shell->command_args[i] = ft_strdup(after_ds);
	free(after_ds);
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

void	expand_multiple(t_minishell *sh, int i, int x, int st)
{
	int		end;
	char	*temp;
	char	*return_str;
	char	*temp_str;

	return_str = 0;
	sh->expander_flag = 0;
	while (sh->command_args[i][st] != '\0')
	{
		end = obtain_end(sh, i, &st);
		while (sh->command_args[i][end] != '$' && sh->command_args[i][end])
			end++;
		temp = ft_substr(sh->command_args[i], st, end - st);
		if (check_var_true(temp, sh) == 1)
			temp_str = expand_multiple2(sh, temp, x);
		else
		{
			sh->expander_flag++;
			free(temp);
			continue ;
		}
		st = end;
		return_str = join_vars(sh, temp_str, return_str);
	}
	expand_multiple_end(sh, i, return_str);
}

char	*expand_multiple2(t_minishell *shell, char *temp, int x)
{
	char	*return_str;
	char	*temp2;

	return_str = 0;
	if (temp[0] == '?')
		return (free(temp), ft_itoa(g_exit_status));
	if (x == 0)
	{
		x = 1;
		temp2 = perform_var_expansion2(shell, temp);
		return_str = ft_strjoin(temp2, "");
		free(temp2);
	}
	else
	{
		temp2 = perform_var_expansion2(shell, temp);
		temp = ft_strdup(return_str);
		free(return_str);
		return_str = ft_strjoin(temp, temp2);
		free(temp2);
		free(temp);
	}
	return (return_str);
}

char	*expand_multiple3(char *temp)
{
	char	*temp2;
	char	*return_str;

	return_str = 0;
	temp2 = ft_strdup(return_str);
	free(return_str);
	return_str = ft_strjoin(temp2, "");
	free(temp);
	free(temp2);
	return (return_str);
}
