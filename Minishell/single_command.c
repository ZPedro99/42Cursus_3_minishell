/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 16:33:11 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	int		i;
	char	*command;

	command = whitespaces(shell->command);
	i = 0;
	while (command[i])
	{
		if (command[i] == ' ' || command[i] == '\t')
			i++;
		else
			break ;
	}
	if (i == (int)ft_strlen(command))
		return (free(command), 0);
	shell->command_args = remove_redirs(command, shell);
	if (!shell->command_args)
	{
		ft_putstr_fd("Minishell: invalid command.\n", 2);
		free(command);
		return (0);
	}
	return (single_command2(shell, command));
}

int	single_command2(t_minishell *shell, char *command)
{
	int	i;

	i = 0;
	if (check_quotes_on_args(shell->command_args, shell))
		return (0);
	ft_expander(shell);
	if (execute_single_cmd(shell, command))
	{
		free_splited(shell->command_args);
		free(command);
		return (1);
	}
	execute_builtins(shell, command);
	if (shell->exit_flag != 1)
		get_exit_status(shell);
	if (!shell->command_args[0])
	{
		free(command);
		free(shell->command_args);
		return (0);
	}
	if (!string_comp(shell->command_args[0], "exit"))
		free(command);
	free_splited(shell->command_args);
	return (0);
}

char	**remove_redirs(char *command, t_minishell *shell)
{
	int		i;
	int		num_words;
	char	**com_args;

	num_words = countwords(command);
	shell->expander_flags = ft_calloc(num_words, sizeof(int));
	com_args = ft_splitting(command, ' ');
	i = -1;
	while (com_args[++i])
	{
		if (check_closed(shell, i, com_args) == 0)
			return (0);
		if (string_comp(com_args[i], ">") || string_comp(com_args[i], ">>")
			|| string_comp(com_args[i], "<") || string_comp(com_args[i], "<<"))
		{
			if (i == num_words - 2)
			{
				free(com_args[i]);
				free(com_args[i + 1]);
				com_args[i] = 0;
				return (com_args);
			}
		}
	}
	return (com_args);
}

int	check_closed(t_minishell *shell, int i, char **com_args)
{
	if (check_closed_quotes(com_args[i]) == 2)
	{
		free(shell->expander_flags);
		free_splited(com_args);
		return (0);
	}
	return (1);
}

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}
