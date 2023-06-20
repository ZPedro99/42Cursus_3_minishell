/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:36:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/20 16:52:51 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_commands(t_minishell *shell)
{
	int	i;

	pipe_creation(shell);
	shell->stdin_fd = STDIN_FILENO;
	shell->stdout_fd = STDOUT_FILENO;
	i = 0;
	shell->command_splited = ft_split(shell->command, '|');
	return (0);
}

int	pipe_creation(t_minishell *shell)
{
	int i;

	shell->pipes_fd = malloc(sizeof(int) * (shell->pipes * 2));
	i = 0;
	if(pipe(shell->pipes_fd + (2 * i)) < 0)
	{
		ft_putstr_fd("Error while creating pipes", 2);
		return (1);
	}
	return (0);
}