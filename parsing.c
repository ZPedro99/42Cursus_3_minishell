/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/20 10:26:37 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_minishell *shell)
{
	t_list	*temp;
	char		*complete;
	char		*name;
	char		*info;
	int			i;

	i = 0;
	while(shell->command_splited[i])
		i++;
	if(i >= 2)
	{
		printf("Error in env\n");
		return (127);
	}
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
	return (0);
}

void	print_exp(t_minishell *shell)
{
	t_list	*temp;
	char	**exp_array;
	//char	*exp_line;
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
				//exp_line = ft_strjoin(exp_array[i], ((t_env *)(temp->content))->info);
				break ;
			}
			temp = temp->next;
		}
		printf("%s%s\n", ((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		//free(exp_line);
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
			free(command);
			free_struct(shell);
			exit(g_exit_status);
		}
	}
	free(command);
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

char *quote_remover_exp(char *str)
{
	int	i;
	char *new;
	char temp;
	int j;

	j = 0;
	i = 0;
	while(str[i] != '\'' && str[i] != '"' && '\0')
		i++;
	if (str[i] == '\0')
	{
		new = ft_strdup(str);
		return (new);
	}
	temp = str[i];
	new = malloc(sizeof(char) * (ft_strlen(str) - counting_quote(str, temp) + 1));
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == temp)
			i++;
		else
		{
			new[j] = str[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
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