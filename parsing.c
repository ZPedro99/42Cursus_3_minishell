/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/30 16:57:03 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_comp(char *s1, char *s2)
{
	if(ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (1);
	return (0);
}

void	print_env(t_minishell *shell)
{
	t_list	*temp;
	char		*completa;

	temp = shell->env;
	while(temp)
	{
		completa = ft_strjoin(((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		printf("%s\n", completa);
		free(completa);
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
	while(exp_array[size])
		size++;
	while((size - 1) != i)
	{
		while(temp)
		{
			if(string_comp(exp_array[i], ((t_env *)(temp->content))->name))
			{
				exp_line = ft_strjoin(exp_array[i], ((t_env *)(temp->content))->info);
				break;
			}
			temp = temp->next;
		}
		free(exp_line);
		printf("%s\n", exp_line);
		temp = shell->exp;
		i++;
	}
	i = 0;
	while(exp_array[i])
	{
		free(exp_array[i]);
		i++;
	}
	free(exp_array);
}

int	len_compare(char *s1, char *s2)
{
	if(ft_strlen(s1) > ft_strlen(s2))
		return(ft_strlen(s1));
	if(ft_strlen(s2) > ft_strlen(s1))
		return(ft_strlen(s2));
	return(ft_strlen(s1));
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
	while(i < size)
	{
		exp_array[i] = ft_strdup(((t_env *)(lst->content))->name);
		i++;
		lst = lst->next;
	}
	exp_array[i] = 0;
	i = 0;
	while(i < size - 1)
	{
		size_string = len_compare(exp_array[i], exp_array[i + 1]);
		if(ft_strncmp(exp_array[i], exp_array[i + 1], size_string) > 0)
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
	i = 0;
	/* while(i < size)
	{
		printf("%s\n", exp_array[i]);
		free(exp_array[i]);
		i++;
	} */
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
	while(temp)
	{
		env_cpy[i] = ft_strjoin(((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		//printf("%s\n", env_cpy[i]);
		temp = temp->next;
		i++;
	}
	return(env_cpy);
}

int	parsing(t_minishell *shell)
{
	pid_t	pid;
	int		i;

	shell->command_splited = ft_split(shell->command, ' ');
	if(string_comp(shell->command_splited[0], "exit"))
	{
		printf("%s\n", shell->command);
		return (1);
	}
	else if(string_comp(shell->command_splited[0], "pwd"))
		print_pwd(shell);
	else if(string_comp(shell->command_splited[0], "cd"))
		print_cd(shell);
	else if(string_comp(shell->command_splited[0], "env"))
		print_env(shell);
	else if(string_comp(shell->command_splited[0], "echo"))
		print_echo(shell);
	else if(string_comp(shell->command_splited[0], "export"))
		print_exp(shell);
	else if(string_comp(shell->command_splited[0], "clear"))
	{
		pid = fork(); //criamos um fork que e um processo child para que o programa continue a correr depois de executarmos o execve
		if (!pid)
			execve("/usr/bin/clear", shell->command_splited, env_copy(shell->env)); //funcao serve para executar um programa ja existente e no final fecha o programa
	}
	else
		printf("%s: command not found\n", shell->command_splited[0]);
	i = 0;
	while(shell->command_splited[i])
	{
		free(shell->command_splited[i]);
		i++;
	}
	free(shell->command_splited[i]);
	free(shell->command_splited);
	return (0);
}
