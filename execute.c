/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/24 15:37:35 by jomirand         ###   ########.fr       */
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
			return (free_child_process(shell, cmd_args, command), exit(0));
		redirect(shell);
		builtin_check(shell, cmd_args, command);
		if (!other_commands(shell, shell->command_args[0], shell->command_args))
		{
			free_child_process(shell, cmd_args, command);
			exit(0);
		}
		free_child_process(shell, cmd_args, command);
		exit(g_exit_status);
	}
	if (!shell->command_args[0])
		return (0);
	execute_builtins(shell, command);
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
		if (other_commands(shell, shell->command_args[0], shell->command_args))
			return (free_child_process_multi(shell, command), exit(0));
		free_splited(shell->command_args);
		free(command);
		free_splited(shell->command_splitted_pipe);
		exit(g_exit_status);
	}
	execute_builtins_multi(shell, command);
	return (0);
}

int	other_commands(t_minishell *shell, char *command, char **command_args)
{
	char			**temp_env;
	char			*command_temp;
	static int		x;

	x = -1;
	i = 0;
	if (check_available_paths(shell->env))
	{
		ft_putstr_fd("Minishell: variable PATH unavailable.\n", 2);
		return (x);
	}
	temp_env = env_copy(shell->env);
	command_temp = ft_strtrim(command, " ");
	execute_execve(command, command_args, temp_env, command_temp);
	if (x == -1)
	{
		ft_putstr_fd("Minishell: command does not exist.\n", 2);
		free_splited(temp_env);
		g_exit_status = 127;
	}
	return (x);
}

void	execute_execve(char *cmd, char **cmd_args, char **tp_env, char *cmd_tp)
{
	char	*temp;
	int		i;
	char	*complete_path;

	i = 0;
	if (execve(cmd, cmd_args, tp_env))
	{
		while (shell->paths[i])
		{
			temp = ft_strjoin("/", cmd_tp);
			complete_path = ft_strjoin(shell->paths[i], temp);
			free(temp);
			if (!access(complete_path, X_OK))
			{
				x = 0;
				execve(complete_path, cmd_args, t_env);
				break ;
			}
			free(complete_path);
			i++;
		}
		free(cmd_tp);
	}
}

void	get_exapander_flags(t_minishell *shell, char *command)
{
	int	num_words;

	num_words = countwords(command);
	shell->expander_flags = ft_calloc(num_words, sizeof(int));
}
