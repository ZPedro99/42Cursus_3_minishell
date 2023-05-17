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
	while(shell->env != NULL)
	{
		printf("%s\n", ((t_env *)(shell->env->content))->info);
		shell->env = shell->env->next;
	}
}

void	print_exp(t_minishell *shell)
{
	while(shell->exp != NULL)
	{
		printf("%s\n", ((t_env *)(shell->exp->content))->info);
		shell->exp = shell->exp->next;
	}
}

int	parsing(char *command, t_minishell *shell)
{
	if(string_comp(command, "exit"))
		return (1);
	if(string_comp(command, "env"))
		print_env(shell);
	if(string_comp(command, "export"))
		print_exp(shell);
	return (0);
}