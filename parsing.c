/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/24 17:04:18 by jomirand         ###   ########.fr       */
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

	temp = shell->env;
	while(temp)
	{
		printf("%s\n", ((t_env *)(temp->content))->info);
		temp = temp->next;
	}
}

void	print_exp(t_minishell *shell)
{
	t_list	*temp;

	temp = shell->exp;
	sort_exp(temp, shell->exp);
}

int	len_compare(char *s1, char *s2)
{
	if(ft_strlen(s1) > ft_strlen(s2))
		return(ft_strlen(s1));
	if(ft_strlen(s2) > ft_strlen(s1))
		return(ft_strlen(s2));
	return(ft_strlen(s1));
}

void	sort_exp(t_list *lst, t_list *head)
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
		exp_array[i] = ((t_env *)(lst->content))->info;
		i++;
		lst = lst->next;
	}
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
	while(i < size)
	{
		printf("%s\n", exp_array[i]);
		free(exp_array[i]);
		i++;
	}
	free(exp_array);
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
		env_cpy[i] = ft_strdup(((t_env *)(temp->content))->info);
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
	if(string_comp(shell->command_splited[0], "pwd"))
		print_pwd(shell);
	if(string_comp(shell->command_splited[0], "env"))
		print_env(shell);
	if(string_comp(shell->command_splited[0], "echo"))
		print_echo(shell);
	if(string_comp(shell->command_splited[0], "export"))
		print_exp(shell);
	if(string_comp(shell->command_splited[0], "clear"))
	{
		pid = fork(); //criamos um fork que e um processo child para que o programa continue a correr depois de executarmos o execve
		if (!pid)
			execve("/usr/bin/clear", shell->command_splited, env_copy(shell->env)); //funcao serve para executar um programa ja existente e no final fecha o programa
	}
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
