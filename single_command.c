/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/21 10:31:44 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	char	*command;

	shell->command_splited = ft_split(shell->command, ' ');
	command = quote_remover(shell->command_splited[0]);
	if(execute(shell, command, 0))
		return (1);
	return (0);
}