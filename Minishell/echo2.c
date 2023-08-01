/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:17:53 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/14 17:40:18 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str && !quote)
	{
		if (ft_strrchr("\"\'", *str))
			quote = *str;
		str++;
	}
	while (*str && quote)
	{
		if (*str && *str == quote)
			quote = 0;
		str++;
	}
	if (*str)
		return (check_closed_quotes(str));
	else if (!quote)
		return (0);
	else
		return (1);
}

int	check_redirect(char *str)
{
	if (string_comp(str, ">"))
		return (1);
	if (string_comp(str, "<"))
		return (1);
	if (string_comp(str, ">>"))
		return (1);
	if (string_comp(str, "<<"))
		return (1);
	return (0);
}

int	check_no_newline_flag(t_minishell *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (shell->command_args[i])
	{
		if (shell->command_args[i][0] == '-'
			&& shell->command_args[i][1] == 'n')
		{
			j = 2;
			while (shell->command_args[i][j])
			{
				if (shell->command_args[i][j] == ' ')
					break ;
				if (shell->command_args[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i - 1);
}

int	echo_no_args(t_minishell *shell)
{
	int	i;
	int	n_count;
	int	word_num;

	i = 1;
	word_num = wordcount(shell->command, ' ');
	n_count = echo_no_args2(shell, i);
	if (n_count == word_num - 1)
		return (1);
	return (0);
}

int	echo_no_args2(t_minishell *shell, int i)
{
	int	j;
	int	n_count;

	n_count = 0;
	while (shell->command_args[i])
	{
		if (shell->command_args[i][0] == '-' 
			&& shell->command_args[i][1] == 'n')
		{
			j = 2;
			while (shell->command_args[i][j] == 'n')
			{
				if (shell->command_args[i][j] == ' ')
					break ;
				if (shell->command_args[i][j] != 'n')
					break ;
				j++;
			}
			if (shell->command_args[i][j] == ' '
				|| shell->command_args[i][j] == '\0')
				n_count++;
		}
		i++;
	}
	return (n_count);
}
