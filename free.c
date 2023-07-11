/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:54:14 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/11 16:24:13 by emsoares         ###   ########.fr       */
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
	if(shell->command_args)
		free_splited(shell->command_args);
	else
		free(shell->command_args);
	if(shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->home);
	free(shell->expander_flags);
	free_export(shell->exp); //por obra do espirito santo nao e preciso este free, cada vez percebo menos
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
	if(shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->expander_flags);
	free(shell->home);
	free_export(shell->exp); //por obra do espirito santo nao e preciso este free, cada vez percebo menos
	free_env(shell->env);
}

void	free_struct_spaces(t_minishell *shell)
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
	if(shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->expander_flags);
	free(shell->home);
	free_export(shell->exp); //por obra do espirito santo nao e preciso este free, cada vez percebo menos
	free_env(shell->env);
}

void	free_splited(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_copies(char **copy)
{
	int	i;

	i = 0;
	while(copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	free_eof(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		free(shell->paths[i]);
		i++;
	}
	free(shell->paths);
	//free(shell->pid);
	free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->expander_flags);
	free(shell->home);
	free_export(shell->exp); //por obra do espirito santo nao e preciso este free, cada vez percebo menos
	free_env(shell->env);
}