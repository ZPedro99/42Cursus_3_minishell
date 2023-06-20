/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/20 11:06:19 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_minishell *shell)
{
	pid_t	pid;
	int		status;
	char	*command;

	status = 0;
	shell->command_splited = ft_split(shell->command, ' ');
	command = quote_remover(shell->command_splited[0]);
	pid = fork();
	if(!pid)
	{
		if (string_comp(command, "exit"))
			exit(0);
		else if (string_comp(command, "pwd"))
		{
			print_pwd(shell);
			exit(0);
		}
		else if (string_comp(command, "cd"))
		{
			exit(0);
		}
		else if (string_comp(command, "unset"))
			exit(0);
		else if (string_comp(command, "env"))
		{
			g_exit_status = print_env(shell);
			exit(g_exit_status);
		}
		else if (string_comp(command, "echo"))
		{
			print_echo(shell);
			exit(0);
		}
		else if (string_comp(command, "export"))
			exit(0);
		else
		{
			if(other_commands(shell) == 0) //exit status ok
				exit(0);
			exit(g_exit_status);
		}
		free_splited(shell);
	}
	wait(&status);
	get_exit_status(status);
	 if (string_comp(command, "export"))
		g_exit_status = check_args(shell->command_splited, shell);
	else if (string_comp(command, "unset"))
		do_unset(shell);
	else if (string_comp(command, "cd"))
	{
		g_exit_status = print_cd(shell);
	}
	else if (string_comp(command, "exit"))
	{
		if (ft_exit_status(shell) != 1)
		{
			free_struct(shell);
			exit(g_exit_status);
		}
	}
	if(shell->command_splited)
		free_splited(shell);
	//get_exit_status(status);
	return (0);
}

int	check_args(char **command, t_minishell *shell)
{
	int	i;
	int	x;
	char	*str;

	i = 1;
	x = 0;
	while (command[i] != NULL)
		i++;
	if(i == 1)
		print_exp(shell);
	if(i >= 2)
	{
		i = 1;
		while(command[i])
		{
			if(check_exp_quotes(command[i]) == 0)
			{
				printf("Error in export variable, check quotes!\n");//se tiver quotes diferentes
				return(1);
			}
			if(check_exp_quotes(command[i]) == -1)
			{
				printf("Error in export variable, quote must have their pair!\n");
				return (1);
			}
			if(check_exp_quotes(command[i]) == 1)
			{
				str = quote_remover_exp(command[i]);
				if(check_exp_input(str) == 0)
				{
					x = 1;
					free(str);
					printf("minishell: export: `%s': not a valid identifier\n", str);
				}
				else
					place_exp_var(shell, str);
				free(str);
			}
			i++;
		}
	}
	if (x == 0)
		return (0);
	return (1);
}

int	check_exp_quotes(char *original)
{
	int i;

	i = 0;
	while (original[i])
	{
		if (original[i] == '"' || original[i] == '\'')
		{
			if (check_equal(original, i) == 0)
				return (0);
			if (check_equal(original, i) == -1)
				return (-1);
			if (check_equal(original, i) == 1)
				return (1);
		}
		i++;
	}
	return (1);
}

int	check_equal(char *str, int i)
{
	char temp;
	int count;

	count = 0;
	temp = str[i];
	if(temp == '\'')
	{
			while(str[i])
			{
				if (str[i] == '"')
					return(0);
				if (str[i] == '\'')
					count++;
				i++;
			}
			if(count % 2 == 0)
				return (1);
			else
				return (-1);
	}
	else if(temp == '"')
	{
		while(str[i])
		{
			if (str[i] == '\'')
				return(0);
			if (str[i] == '"')
				count++;
			i++;
		}
		if(count % 2 == 0)
			return (1);
		else
			return (-1);
	}
	return(0);
}

int	other_commands(t_minishell *shell)
{
	int		i;
	char	*complete_path;
	char	**temp;
	pid_t	pid;
	static int		x;

	x = -1;
	i = 0;
	if(check_available_paths(shell->env))
	{
		printf("Error! PATH unavailable!\n");
		return(x);
	}
	temp = env_copy(shell->env);
	if(execve(shell->command_splited[0], shell->command_splited, temp))
	{
		free_copies(temp);
		while (shell->paths[i])
		{
			temp = malloc(sizeof(char *) * 2);
			temp[0] = ft_strjoin("/", shell->command_splited[0]);
			temp[1] = 0;
			complete_path = ft_strjoin(shell->paths[i], temp[0]);
			free_copies(temp);
			temp = env_copy(shell->env);
			if (!access(complete_path, X_OK))
			{
				x = 0;
				pid = fork();
				if(!pid)
					execve(complete_path, shell->command_splited, temp);
				wait(0);
				free(complete_path);
				free_copies(temp);
				break ;
			}
			free(complete_path);
			free_copies(temp);
			i++;
		}
	}
	if(x == -1)
	{
		perror("other commands");
		g_exit_status = 127; //nao esta a assumir !!!!
	}
	return (x);
}

int	check_available_paths(t_list *env)
{
	t_list	*temp;

	temp = env;
	while(temp)
	{
		if(string_comp(((t_env *)(temp->content))->name, "PATH="))
			return (0);
		temp = temp->next;
	}
	return (1);
}

char	*remove_quotes(char *command)
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
}