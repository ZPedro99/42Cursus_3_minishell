/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:36:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/03 09:40:17 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_commands(t_minishell *shell)
{
	int	i;

	shell->stdin_fd = STDIN_FILENO;
	shell->stdout_fd = STDOUT_FILENO;
	shell->command_args = ft_split(shell->command, '|');
	i = 0;
	pipe_creation(shell);
	while(shell->command_args[i])
	{
		shell->command_splitted = ft_split(shell->command_args[i], ' ');
		execute_multi_cmd(shell, shell->command_splitted[0], i);
		free_splited(shell->command_splitted);
		i++;
	}
	pipe_closing(shell);
	get_exit_status(shell);
	return (0);
}

int	pipe_creation(t_minishell *shell)
{
	int i;

	shell->pipes_fd = malloc(sizeof(int) * (shell->pipes * 2));
	i = 0;
	while(i < shell->pipes)
	{
		if(pipe(shell->pipes_fd + (2 * i)) < 0)
		{
			ft_putstr_fd("Error while creating pipes", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	through_pipes(t_minishell *shell, int i)
{
	if(i == 0)
	{
		//close(shell->pipes_fd[0]);
		//dup2(shell->stdin_fd, STDIN_FILENO);
		dup2(shell->pipes_fd[1], STDOUT_FILENO);
		//close(shell->pipes_fd[1]);
	}
	else if(i == shell->pipes)
	{
		//close(shell->pipes_fd[1]);
		dup2(shell->pipes_fd[2 * i - 2], STDIN_FILENO);
		//dup2(shell->stdout_fd, STDOUT_FILENO);
		//close(shell->pipes_fd[0]);
	}
	else
	{
		dup2(shell->pipes_fd[2 * i - 2], STDIN_FILENO);
		dup2(shell->pipes_fd[2 * i + 1], STDOUT_FILENO);
	}
	pipe_closing(shell);
}

void	pipe_closing(t_minishell *shell)
{
	int	i;

	i = 0;
	while(i < shell->pipes * 2)
	{
		close(shell->pipes_fd[i]);
		i++;
	}
}
