/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:06 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/17 14:28:06 by jomirand         ###   ########.fr       */
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
	while(temp)
	{
		printf("%s\n", ((t_env *)(temp->content))->info);
		temp = temp->next;
	}
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
	char	**clear_test;
	
	clear_test = malloc(sizeof(char *) * 2);
	clear_test[0] = shell->command;
	clear_test[1] = NULL;
	if(string_comp(shell->command, "exit"))
		return (1);
	if(string_comp(shell->command, "env"))
		print_env(shell);
	if(string_comp(shell->command, "export"))
		print_exp(shell);
	if(string_comp(shell->command, "clear"))
	{
		pid = fork();
		if (!pid)
			execve("/usr/bin/clear", clear_test, env_copy(shell->env));
	}
	return (0);
}