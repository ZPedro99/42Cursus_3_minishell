/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:03:13 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 10:17:13 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(t_minishell *sh, char **cmd_args, char *cmd)
{
	if (string_comp(sh->command_args[0], "exit"))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	if (string_comp(sh->command_args[0], "pwd"))
	{
		print_pwd(sh);
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "cd"))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	builtin_check2(sh, cmd_args, cmd);
	return (0);
}

int	builtin_check2(t_minishell *sh, char **cmd_args, char *cmd)
{
	if (string_comp(sh->command_args[0], "unset"))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "env"))
	{
		g_exit_status = print_env(sh);
		free_child_p(sh, cmd_args, cmd);
		exit(g_exit_status);
	}
	else if (string_comp(sh->command_args[0], "echo"))
	{
		print_echo(sh);
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "export"))
	{
		check_export_args(sh);
		free_child_p(sh, cmd_args, cmd);
		exit(0);
	}
	return (0);
}

int	builtin_check_multi(t_minishell *sh, char *cmd)
{
	if (string_comp(sh->command_args[0], "exit"))
	{
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "pwd"))
	{
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "cd"))
	{
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	builtin_check_multi2(sh, cmd);
	return (0);
}

int	builtin_check_multi2(t_minishell *sh, char *cmd)
{
	if (string_comp(sh->command_args[0], "unset"))
	{
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "env"))
	{
		g_exit_status = print_env(sh);
		free_child_process_multi(sh, cmd);
		exit(g_exit_status);
	}
	else if (string_comp(sh->command_args[0], "echo"))
	{
		print_echo(sh);
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	else if (string_comp(sh->command_args[0], "export"))
	{
		print_exp(sh);
		free_child_process_multi(sh, cmd);
		exit(0);
	}
	return (0);
}
