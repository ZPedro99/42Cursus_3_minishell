/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:15:00 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 12:27:16 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_paths(char *paths)
{
	int	number;
	int	i;

	number = 1;
	i = 0;
	while (paths[i])
	{
		if (paths[i] == ':')
			number++;
		i++;
	}
	return (number);
}

int	check_command(t_minishell *shell)
{
	char	**cmd_args;

	if (!shell->command)
	{
		printf("exit\n");
		free_eof(shell);
		exit (0);
	}
	cmd_args = ft_splitting(shell->command, '|');
	if (check_closed_quotes(shell->command) == 1)
	{
		ft_putstr_fd("minishell: error: unclosed quotes\n", 2);
		free_splited(cmd_args);
		return (1);
	}
	if (check_command2(cmd_args) == 1)
		return (1);
	return (0);
}

int	check_command2(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (ft_strrchr("><", cmd_args[i][0]) && i > 0)
		{
			free_splited(cmd_args);
			ft_putstr_fd("Minishell: error near pipe\n", 2);
			return (1);
		}
		i++;
	}
	free_splited(cmd_args);
	return (0);
}
