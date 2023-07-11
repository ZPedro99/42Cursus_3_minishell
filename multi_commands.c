/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:36:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/11 16:24:54 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_commands(t_minishell *shell)
{
	int		i;
	char	*command;
	//char	*str_nospace;
	//char	*cmd_no_quotes;

	shell->stdin_fd = STDIN_FILENO;
	shell->stdout_fd = STDOUT_FILENO;
	shell->command_splitted_pipe = ft_split(shell->command, '|');
	i = 0;
	pipe_creation(shell);
	while(shell->command_splitted_pipe[i])
	{
		command = whitespaces(shell->command_splitted_pipe[i]);
		/* shell->command_splitted = ft_split(shell->command_splitted_pipe[i], ' ');
		str_nospace = remove_last_space(shell->command_splitted_pipe[i]);
		shell->command_args = remove_redirs(str_nospace);
		cmd_no_quotes = quote_remover(shell->command_splitted[0]);
		//free(shell->command_splitted[0]);
		shell->command_splitted[0] = ft_strdup(cmd_no_quotes);
		free(cmd_no_quotes); */
		execute_multi_cmd(shell, command, i);
		//free_splited(shell->command_splitted);
		//free(str_nospace);
		free(command);
		i++;
	}
	free_splited(shell->command_splitted_pipe);
	free(shell->expander_flags);
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
	free(shell->pipes_fd);
}

char	*remove_last_space(char *str)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while(str[i])
	{
		if(str[i] == ' ' && str[i + 1] == '\0')
		{
			new_str[i] = '\0';
			break ;
		}
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}