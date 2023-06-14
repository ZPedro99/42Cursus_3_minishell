/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/14 10:10:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_minishell *shell)
{
	t_list	*temp;
	char	*complete;
	char	*name;
	char	*info;

	temp = shell->env;
	while (temp)
	{
		name = ft_strdup(((t_env *)(temp->content))->name);
		info = ft_strdup(((t_env *)(temp->content))->info);
		complete = ft_strjoin(name, info);
		printf("%s\n", complete);
		free(complete);
		free(name);
		free(info);
		temp = temp->next;
	}
}

void	print_exp(t_minishell *shell)
{
	t_list	*temp;
	char	**exp_array;
	char	*exp_line;
	int		i;
	int		size;

	i = 0;
	size = 0;
	temp = shell->exp;
	exp_array = sort_exp(temp, shell->exp);
	while (exp_array[size])
		size++;
	while (size != i)
	{
		while (temp)
		{
			if (string_comp(exp_array[i], ((t_env *)(temp->content))->name))
			{
				exp_line = ft_strjoin(exp_array[i], ((t_env *)(temp->content))->info);
				break ;
			}
			temp = temp->next;
		}
		printf("%s\n", exp_line);
		free(exp_line);
		temp = shell->exp;
		i++;
	}
	i = 0;
	while (exp_array[i])
	{
		free(exp_array[i]);
		i++;
	}
	free(exp_array);
}

char	**sort_exp(t_list *lst, t_list *head)
{
	int		size;
	int		size_string;
	char	**exp_array;
	int		i;
	char	*temp1;
	char	*temp2;

	(void)head;
	i = 0;
	size = ft_lstsize(lst);
	exp_array = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		exp_array[i] = ft_strdup(((t_env *)(lst->content))->name);
		i++;
		lst = lst->next;
	}
	exp_array[i] = 0;
	i = 0;
	while (i < size - 1)
	{
		size_string = len_compare(exp_array[i], exp_array[i + 1]);
		if (ft_strncmp(exp_array[i], exp_array[i + 1], size_string) > 0)
		{
			temp1 = ft_strdup(exp_array[i]);
			temp2 = ft_strdup(exp_array[i + 1]);
			free(exp_array[i]);
			free(exp_array[i + 1]);
			exp_array[i] = ft_strdup(temp2);
			exp_array[i + 1] = ft_strdup(temp1);
			free(temp1);
			free(temp2);
			i = 0;
		}
		else
			i++;
	}
	return (exp_array);
}

char	**env_copy(t_list *lst)
{
	char	**env_cpy;
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	env_cpy = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (temp)
	{
		env_cpy[i] = ft_strjoin(((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		temp = temp->next;
		i++;
	}
	env_cpy[i] = 0;
	return (env_cpy);
}

int	parsing(t_minishell *shell)
{
	pid_t	pid;
	int		i;
	int		status;

	status = 0;
	i = 0;
	shell->command_splited = ft_split(shell->command, ' ');
	pid = fork();
	if(!pid)
	{
		if (string_comp(shell->command_splited[0], "exit"))
		{
			printf("%s\n", shell->command_splited[0]);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "pwd"))
		{
			print_pwd(shell);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "cd"))
		{
			print_cd(shell);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "env"))
		{
			print_env(shell);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "echo"))
		{
			print_echo(shell);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "export"))
		{
			check_args(shell->command_splited, shell);
			exit(0);
		}
		else if (string_comp(shell->command_splited[0], "unset"))
		{
			do_unset(shell);
			exit(0);
		}
		else
		{
			other_commands(shell);
			exit(0);
		}
		free_splited(shell);
	}
	wait(&status);
	if (string_comp(shell->command_splited[0], "exit"))
	{
		free_struct(shell);
		exit(g_exit_status);
	}
	if(shell->command_splited)
		free_splited(shell);
	get_exit_status(status);
	return (0);
}

void	check_args(char **command, t_minishell *shell)
{
	int	i;

	i = 1;
	while (command[i] != NULL)
		i++;
	if(i == 1)
		print_exp(shell);
	if(i >= 2)
	{
		i = 1;
		while(command[i])
		{
			if(check_exp_input(command[i]) == 0)
				printf("minishell: export: `%s': not a valid identifier\n", command[i]);
			else
				place_exp_var(shell, shell->command_splited[i]);
			i++;
		}
	}
}

int	check_exp_input(char *str)
{
	int		i;
	char	*temp;
	char	*temp1;
	temp = get_var_name(str);
	if (ft_search(temp, '=') == 1)
	{
		temp1 = ft_strdup(temp);
		free(temp);
		temp = ft_strtrim(temp1, "=");
		free(temp1);
	}
	if ((ft_isalpha(temp[0]) == 0) && temp[0] != '_')
	{
		free(temp);
		return (0);
	}
	i = 0;
	while (temp[i])
	{
		if ((ft_isalnum(temp[i]) == 1) || temp[i] == '_' )
			i++;
		else
		{
			free(temp);
			return (0);
		}
	}
	free(temp);
	return (1);
}

void	other_commands(t_minishell *shell)
{
	int		i;
	char	*complete_path;
	char	**temp;
	pid_t	pid;
	static int		x;

	x = -1;
	i = 0;
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
		//printf("%s: command not found\n", shell->command_splited[0]);
		perror("Error");
	}
}
