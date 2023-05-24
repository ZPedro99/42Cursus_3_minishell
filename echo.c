/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/24 10:57:33 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	char	**execute;
	int		i;

	execute = ft_split(shell->command, ' ');
	i = 1;
	while(execute[i])
	{
		printf("%s ", execute[i]);
		i++;
	}
	i = 0;
	while(execute[i])
	{
		free(execute[i]);
		i++;
	}
	free(execute);
	printf("\n");
}