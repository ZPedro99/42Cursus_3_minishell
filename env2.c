/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:00:24 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/05 15:22:32 by jomirand         ###   ########.fr       */
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
	while(shell->command_args[i])
		i++;
	if(i >= 2)
	{
		ft_putstr_fd("Minishell: wrong number of arguments.\n", 2);
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