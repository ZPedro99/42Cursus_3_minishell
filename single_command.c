/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/28 10:43:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	char	*command;

	shell->command_splited = ft_split(shell->command, ' ');
	command = quote_remover(shell->command_splited[0]);
	//free(shell->command_splited[0]);
	shell->command_splited[0] = ft_strdup(command);
	free(command);
	if(execute_single_cmd(shell, shell->command_splited[0]))
		return (1);
	free_splited(shell->command_splited);
	return (0);
}