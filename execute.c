/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/07 14:50:56 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_cmd(t_minishell *shell, char *command)
{
	//int		status;
	//int	j;
	char	**cmd_args;

	//status = 0;
	//j = 0;
	//shell->command_args = ft_split(shell->command_splitted[i], ' ');
	shell->pid[0] = fork();
	if(!shell->pid[0])
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cmd_args = handle_redirects(shell, command);
		//through_pipes(shell, i);
		dup2(shell->stdin_fd, STDIN_FILENO);
		dup2(shell->stdout_fd, STDOUT_FILENO);
		if (string_comp(shell->command_args[0], "exit"))
		{
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			//free_splited(shell->command_args);
			exit(0);
		}
		if (string_comp(shell->command_args[0], "pwd"))
		{
			print_pwd(shell);
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(0);
		}
		else if (string_comp(shell->command_args[0], "cd"))
		{
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(0);
		}
		else if (string_comp(shell->command_args[0], "unset"))
		{
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(0);
		}
		else if (string_comp(shell->command_args[0], "env"))
		{
			g_exit_status = print_env(shell);
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(g_exit_status);
		}
		else if (string_comp(shell->command_args[0], "echo"))
		{
			print_echo(shell);
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(0);
		}
		else if (string_comp(shell->command_args[0], "export"))
		{
			check_export_args(shell);
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(0);
		}
		else
		{
			if(other_commands(shell, shell->command_args[0], cmd_args) == 0)
			{
				free_struct(shell);
				free(command);
				free_splited(cmd_args);
				exit(0);
			}
			free_struct(shell);
			free(command);
			free_splited(cmd_args);
			exit(g_exit_status);
		}
		//free_struct(shell);
		//free_splited(shell->command_args);
	}
	/* close(shell->pipes_fd[0]);
	close(shell->pipes_fd[1]); */
	//get_exit_status(status);
	 if (string_comp(shell->command_args[0], "export"))
		g_exit_status = check_args(shell->command_args, shell);
	else if (string_comp(shell->command_args[0], "unset"))
		do_unset(shell);
	else if (string_comp(shell->command_args[0], "cd"))
	{
		g_exit_status = do_cd(shell);
	}
	else if (string_comp(shell->command_args[0], "exit"))
	{
		free(command);
		if (ft_exit_status(shell) != 1)
		{
			free_struct(shell);
			exit(g_exit_status);
		}
	}
	//get_exit_status(status);
	/* if(shell->command_splitted)
		free_splited(shell->command_splitted); */
	return (0);
}

int	execute_multi_cmd(t_minishell *shell, char *command, int i)
{
	int		status;
	char	**cmd_args;

	status = 0;
	//shell->command_args = ft_split(shell->command_splitted[i], ' ');
	shell->pid[i] = fork();
	if(!shell->pid[i])
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cmd_args = handle_redirects(shell, command);
		through_pipes(shell, i);
		/* if(i > 0)
		{
			dup2(shell->stdin_fd, STDIN_FILENO);
			dup2(shell->stdout_fd, STDOUT_FILENO);
		} */
		if (string_comp(command, "exit"))
		{
			free_struct(shell);
			exit(0);
		}
		else if (string_comp(command, "pwd"))
		{
			print_pwd(shell);
			free_struct(shell);
			exit(0);
		}
		else if (string_comp(command, "cd"))
		{
			free_struct(shell);
			exit(0);
		}
		else if (string_comp(command, "unset"))
		{
			free_struct(shell);
			exit(0);
		}
		else if (string_comp(command, "env"))
		{
			g_exit_status = print_env(shell);
			free_struct(shell);
			exit(g_exit_status);
		}
		else if (string_comp(command, "echo"))
		{
			print_echo(shell);
			free_struct(shell);
			exit(0);
		}
		else if (string_comp(command, "export"))
		{
			if(!shell->command_args[1])
				print_exp(shell);
			free_struct(shell);
			exit(0);
		}
		else
		{
			if(other_commands(shell, command, shell->command_args) == 0)
			{
				free_struct(shell);
				exit(0);
			}
			exit(g_exit_status);
		}
		//free_splited(shell->command_args);
	}
	//wait(&status);
	//get_exit_status(status);
	 if (string_comp(command, "export"))
		g_exit_status = check_args(shell->command_splitted, shell);
	else if (string_comp(command, "unset"))
		do_unset(shell);
	else if (string_comp(command, "cd"))
	{
		g_exit_status = do_cd(shell);
	}
	else if (string_comp(command, "exit"))
	{
		if (ft_exit_status(shell) != 1)
		{
			free_struct(shell);
			exit(g_exit_status);
		}
	}
	//get_exit_status(status);
	/* if(shell->command_splitted)
		free_splited(shell->command_splitted); */
	return (0);
}

int	other_commands(t_minishell *shell, char *command, char **command_args)
{
	int		i;
	char	*complete_path;
	char	*temp;
	char	**temp_env;
	char	*command_temp;
	static int		x;

	x = -1;
	i = 0;
	if(check_available_paths(shell->env))
	{
		ft_putstr_fd("Minishell: variable PATH unavailable.\n", 2);
		return(x);
	}
	temp_env = env_copy(shell->env);
	command_temp = ft_strtrim(command, " ");
	if(execve(command, command_args, temp_env))
	{
		//free_copies(temp);
		while (shell->paths[i])
		{
			//temp = malloc(sizeof(char *) * 2);
			temp= ft_strjoin("/", command_temp);
			//temp[1] = 0;
			complete_path = ft_strjoin(shell->paths[i], temp);
			free(temp);
			//temp = env_copy(shell->env);
			if (!access(complete_path, X_OK))
			{
				x = 0;
				execve(complete_path, command_args, temp_env);
				/* dup2(shell->stdin_fd, STDIN_FILENO);
				dup2(shell->stdout_fd, STDOUT_FILENO);
				free(complete_path); */
				//free_copies(temp);
				break ;
			}
			free(complete_path);
			//free(temp);
			i++;
		}
		free(command_temp);
	}
	if(x == -1)
	{
		ft_putstr_fd("Minishell: command does not exist.\n", 2);
		free_splited(temp_env);
		g_exit_status = 127; //nao esta a assumir !!!!
	}
	//free_splited(temp_env);
	return (x);
}

/* char	*remove_quotes(char *command)
{
	char *str;
	int i;
	int j;
	int len;

	i = 1;
	j = 0;
	len = strlen(command);
	if (len >= 2 && (command[0] == '"' || command[0] == '\'') && command[len - 1] == command[0])
	{
		str = malloc(sizeof(char) * (len - 1));
	while(i < len - 1)
	{
		str[j] = command[i];
			i++;
			j++;
	}
	str[j] = '\0';
		return (str);
	}
	str = ft_strdup(command);
	return (str);
} */
