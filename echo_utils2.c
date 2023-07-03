/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:28:51 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/13 22:28:51 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_es(t_minishell *shell, int i)
{
	char	*str;
	char	*no_dollar;
	char	*new_str;

	str = ft_strtrim(shell->command_args[i], "$?");
	if (shell->command_args[i][1] == '?')
	{
		printf("%d%s", g_exit_status, str);
		free(str);
		return (0);
	}
	else
	{
		no_dollar = ft_strtrim(shell->command_args[i], "$");
		if(check_closed_quotes(no_dollar))
		{
			write(1, "Error", 5);
			return (0);
		}
		new_str = quote_remover(no_dollar);
		if(!new_str)
			return (0);
		handle_quotes(new_str);
		free(new_str);
		free(no_dollar);
	}
	free (str);
	return (1);
}
