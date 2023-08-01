/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 11:45:09 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("invalid number of arguments!", 2);
		return (1);
	}
	rl_clear_history();
	shell.pipes = 0;
	shell.env = get_env_vars(envp);
	shell.exp = get_exp_vars(envp);
	obtain_vars(&shell);
	get_prompt(&shell);
	read_command(&shell);
	free_struct(&shell);
	return (g_exit_status);
}

void	obtain_vars(t_minishell *shell)
{
	t_list	*temp;

	temp = shell->env;
	while (temp)
	{
		if (string_comp(((t_env *)(temp->content))->name, "PWD="))
			shell->pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "OLDPWD="))
			shell->old_pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "HOME="))
			shell->home = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "PATH="))
			shell->paths = save_paths(((t_env *)(temp->content))->info);
		temp = temp->next;
	}
}

void	read_command(t_minishell *shell)
{
	while (1)
	{
		shell->pipes = 0;
		shell->stdin_fd = 0;
		shell->stdout_fd = 1;
		shell->exit_flag = 0;
		handle_signals();
		shell->command = readline(shell->prompt);
		add_history(shell->command);
		if (check_command(shell))
			continue ;
		if (!*shell->command)
			free(shell->command);
		else
		{
			if (counting_pipes(shell) == -1)
				continue ;
			else if (read_command2(shell) == 0)
				break ;
			free(shell->pid);
			free(shell->command);
		}
	}
	free_splited(shell->command_args);
	rl_clear_history();
}

int	read_command2(t_minishell *shell)
{
	if (counting_pipes(shell) == 0)
	{
		shell->pid = malloc(sizeof(int) * (shell->pipes + 1));
		if (single_command(shell) == 1)
			return (0);
	}
	else if (counting_pipes(shell) > 0)
	{
		shell->pid = malloc(sizeof(int) * (shell->pipes + 1));
		if (multi_commands(shell) == 1)
			return (0);
	}
	return (1);
}

char	**save_paths(char *paths)
{
	char	**paths_array;
	int		i;

	(void)i;
	i = 0;
	paths_array = ft_split(paths, ':');
	return (paths_array);
}
