/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:00:24 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/14 17:45:06 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_minishell *shell)
{
	t_list	*temp;
	char	*complete;
	char	*name;
	char	*info;
	int		i;

	i = 0;
	while (shell->command_args[i])
		i++;
	if (i >= 2)
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
		free_temps(complete, name, info);
		temp = temp->next;
	}
	return (0);
}

void	free_temps(char *a, char *b, char *c)
{
	free(a);
	free(b);
	free(c);
}
