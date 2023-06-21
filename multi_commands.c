/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:36:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/21 12:49:09 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_commands(t_minishell *shell)
{
	int	i;

	pipe_creation(shell);
	shell->stdin_fd = STDIN_FILENO;
	shell->stdout_fd = STDOUT_FILENO;
	shell->command_splited = ft_split(shell->command, '|');
	i = 0;
	while(shell->command_splited[i])
	{
		through_pipes(shell, i);
		execute(shell, shell->command_splited[i], i);
		i++;
	}
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

void	through_pipes(t_minishell *shell, int i)
{
	if(i == 0)
	{
		dup2(shell->stdin_fd, STDIN_FILENO);
		dup2(shell->pipes_fd[1], STDOUT_FILENO);
	}
	if(i == 1)
	{
		dup2(shell->pipes_fd[0], STDIN_FILENO);
		dup2(shell->stdout_fd, STDOUT_FILENO);
	}
}