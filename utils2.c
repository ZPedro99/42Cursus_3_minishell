/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:47:25 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/20 15:37:58 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return (0);
}

int	counting_pipes(t_minishell *shell)
{
	int	i;

	i = 0;
	while(shell->command[i])
	{
		if(shell->command[i] == '|')
			shell->pipes++;
		i++;
	}
	return(shell->pipes);
}