/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:54:14 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/25 16:08:39 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while(temp)
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
	while(temp)
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
	while(temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(temp->content);
		free(temp);
		temp = next;
	}
}