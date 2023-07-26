/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:44:29 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/26 09:27:36 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_args(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->command_args[i])
		i++;
	if (i == 1)
		print_exp(shell);
	else if (i > 1)
		return ;
}

int	check_pipe(int i, char **verify_cmds, int num_words)
{
	if (i == 0)
	{
		if (check_pipe1(verify_cmds, i) == -1)
			return (-1);
	}
	else if (i == num_words - 1)
	{
		if (check_pipe2(verify_cmds, i) == -1)
			return (-1);
	}
	return (0);
}
