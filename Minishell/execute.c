/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/25 12:47:46 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_cmd(t_minishell *shell, char *command)
{
	char	**cmd_args;

	shell->pid[0] = fork();
	if (!shell->pid[0])
	{
		signal_default();
		cmd_args = handle_redirects(shell, command);
		if (!cmd_args[0])
		{
			free_child_p(shell, cmd_args, command);
			exit(0);
		}
		redirect(shell);
		builtin_check(shell, cmd_args, command);
		if (!other_cmds(shell, shell->command_args[0], shell->command_args))
		{
			free_child_p(shell, cmd_args, command);
			exit(0);
		}
		free_child_p(shell, cmd_args, command);
		exit(g_exit_status);
	}
	if (!shell->command_args[0])
		return (0);
	return (0);
}

int	execute_multi_cmd(t_minishell *shell, char *command, int i)
{
	int		status;

	status = 0;
	shell->pid[i] = fork();
	if (!shell->pid[i])
	{
		signal_default();
		shell->command_args = handle_redirects(shell, command);
		get_exapander_flags(shell, command);
		ft_expander(shell);
		through_pipes(shell, i);
		redirect(shell);
		builtin_check_multi(shell, command);
		if (other_cmds(shell, shell->command_args[0], shell->command_args))
		{
			free_child_process_multi(shell, command);
			exit(0);
		}
		free_splited(shell->command_args);
		free(command);
		free_splited(shell->command_splitted_pipe);
		exit(g_exit_status);
	}
	execute_builtins_multi(shell, command);
	return (0);
}

int	other_cmds(t_minishell *shell, char *command, char **command_args)
{
	char	**temp_env;
	char	*command_temp;

	if (check_available_paths(shell->env))
	{
		ft_putstr_fd("Minishell: variable PATH unavailable.\n", 2);
		return (-1);
	}
	temp_env = env_copy(shell->env);
	command_temp = ft_strtrim(command, " ");
	if (e_execve(shell, command, command_args, command_temp))
	{
		ft_putstr_fd("Minishell: command does not exist.\n", 2);
		free_splited(temp_env);
		g_exit_status = 127;
	}
	return (1);
}

int	e_execve(t_minishell *sh, char *cmd, char **cmd_args, char *cmd_tp)
{
	char	*temp;
	int		i;
	char	*complete_path;
	char	**tp_env;

	i = 0;
	tp_env = env_copy(sh->env);
	if (execve(cmd, cmd_args, tp_env))
	{
		while (sh->paths[i])
		{
			temp = ft_strjoin("/", cmd_tp);
			complete_path = ft_strjoin(sh->paths[i], temp);
			free(temp);
			if (!access(complete_path, X_OK))
				execve(complete_path, cmd_args, tp_env);
			free(complete_path);
			i++;
		}
		free_splited(tp_env);
		free(cmd_tp);
	}
	return (1);
}

void	get_exapander_flags(t_minishell *shell, char *command)
{
	int	num_words;

	num_words = countwords(command);
	shell->expander_flags = ft_calloc(num_words, sizeof(int));
}
