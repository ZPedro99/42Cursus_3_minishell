/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/01 12:43:19 by emsoares         ###   ########.fr       */
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
	env_cpy = (char **)malloc(sizeof(char *) * ft_lstsize(lst) + 1);
	while (temp)
	{
		env_cpy[i] = ft_strjoin(((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		temp = temp->next;
		i++;
	}
	return (env_cpy);
}

int	parsing(t_minishell *shell)
{
	pid_t	pid;
	int		i;

	shell->command_splited = ft_split(shell->command, ' ');
	if (string_comp(shell->command_splited[0], "exit"))
	{
		printf("%s\n", shell->command);
		return (1);
	}
	else if (string_comp(shell->command_splited[0], "pwd"))
		print_pwd(shell);
	else if (string_comp(shell->command_splited[0], "cd"))
		print_cd(shell);
	else if (string_comp(shell->command_splited[0], "env"))
		print_env(shell);
	else if (string_comp(shell->command_splited[0], "echo"))
		print_echo(shell);
	else if (string_comp(shell->command_splited[0], "export"))
	{
		if(shell->command_splited[1] != NULL)
			place_exp_var(shell, shell->command_splited[1]);
		else
			print_exp(shell);
	}
	else if (string_comp(shell->command_splited[0], "clear"))
	{
		pid = fork(); //criamos um fork que e um processo child para que o programa continue a correr depois de executarmos o execve
		if (!pid)
			execve("/usr/bin/clear", shell->command_splited, env_copy(shell->env)); //funcao serve para executar um programa ja existente e no final fecha o programa
	}
	else if (string_comp(shell->command_splited[0], "unset"))
		do_unset(shell);
	else
		printf("%s: command not found\n", shell->command_splited[0]);
	i = 0;
	while (shell->command_splited[i])
	{
		free(shell->command_splited[i]);
		i++;
	}
	free(shell->command_splited[i]);
	free(shell->command_splited);
	return (0);
}
