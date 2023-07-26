/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 11:43:59 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtins(t_minishell *shell, char *command)
{
	if (string_comp(shell->command_args[0], "export"))
		g_exit_status = check_args(shell->command_args, shell);
	else if (string_comp(shell->command_args[0], "unset"))
		do_unset(shell);
	else if (string_comp(shell->command_args[0], "cd"))
		g_exit_status = do_cd(shell);
	else if (string_comp(shell->command_args[0], "exit"))
	{
		free(command);
		if (ft_exit_status(shell) != 1)
		{
			free_struct(shell);
			exit(g_exit_status);
		}
		shell->exit_flag = 1;
	}
}

void	execute_builtins_multi(t_minishell *shell, char *command)
{
	if (string_comp(command, "export"))
		g_exit_status = check_args(shell->command_splitted, shell);
	else if (string_comp(command, "unset"))
		do_unset(shell);
	else if (string_comp(command, "cd"))
		g_exit_status = do_cd(shell);
	else if (string_comp(command, "exit"))
	{
		if (ft_exit_status(shell) != 1)
		{
			free_struct(shell);
			exit(g_exit_status);
		}
	}
}
