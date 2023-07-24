/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:03:13 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/24 15:34:49 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(t_minishell *sh, char **cmd_args, char *cmd)
{
	if (string_comp(sh->command_args[0], "exit"))
		return (free_child_process(sh, cmd_args, cmd), exit(0));
	if (string_comp(sh->command_args[0], "pwd"))
		return (print_pwd(sh), free_child_process(sh, cmd_args, cmd), exit(0));
	else if (string_comp(sh->command_args[0], "cd"))
		return (free_child_process(sh, cmd_args, cmd), exit(0));
	else if (string_comp(sh->command_args[0], "unset"))
		return (free_child_process(sh, cmd_args, cmd), exit(0));
	else if (string_comp(sh->command_args[0], "env"))
	{
		g_exit_status = print_env(sh);
		return (free_child_process(sh, cmd_args, cmd), exit(g_exit_status));
	}
	else if (string_comp(sh->command_args[0], "echo"))
	{
		print_echo(sh);
		return (free_child_process(sh, cmd_args, cmd), exit(0));
	}
	else if (string_comp(sh->command_args[0], "export"))
	{
		check_export_args(sh);
		return (free_child_process(sh, cmd_args, cmd), exit(0));
	}
}

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
	}
}

int	builtin_check_multi(t_minishell *sh, char *cmd)
{
	if (string_comp(sh->command_args[0], "exit"))
		return (free_child_process_multi(sh, command), exit(0));
	else if (string_comp(sh->command_args[0], "pwd"))
		return (print_pwd(sh), free_child_process_multi(sh, command), exit(0));
	else if (string_comp(sh->command_args[0], "cd"))
		return (free_child_process_multi(sh, command), exit(0));
	else if (string_comp(sh->command_args[0], "unset"))
		return (free_child_process_multi(sh, command), exit(0));
	else if (string_comp(sh->command_args[0], "env"))
	{
		g_exit_status = print_env(sh);
		return (free_child_process_multi(sh, command), exit(g_exit_status));
	}
	else if (string_comp(sh->command_args[0], "echo"))
	{
		print_echo(sh);
		return (free_child_process_multi(sh, command), exit(0));
	}
	else if (string_comp(sh->command_args[0], "export"))
	{
		print_exp(sh);
		return (free_child_process_multi(sh, command), exit(0));
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
