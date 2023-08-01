/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:54:14 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 09:30:42 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(((t_env *)(temp->content))->info);
		free(temp->content);
		free(temp);
		temp = next;
	}
}

void	free_export(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(((t_env *)(temp->content))->info);
		free(temp->content);
		free(temp);
		temp = next;
	}
}

void	free_export1(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(temp->content);
		free(temp);
		temp = next;
	}
}

void	free_struct(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		free(shell->paths[i]);
		i++;
	}
	free(shell->paths);
	free(shell->pid);
	if (shell->command_args)
		free_splited(shell->command_args);
	else
		free(shell->command_args);
	if (shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->home);
	free_export(shell->exp);
	free_env(shell->env);
}

void	free_struct_multi(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		free(shell->paths[i]);
		i++;
	}
	free(shell->paths);
	free(shell->pid);
	if (shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->home);
	free_export(shell->exp);
	free_env(shell->env);
}
