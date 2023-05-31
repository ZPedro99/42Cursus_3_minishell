/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/31 10:30:11 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	int			i;

	i = 0;
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("invalid number of arguments!", 2);
		return (1);
	}
	shell.env = get_env_vars(envp);
	shell.exp = get_exp_vars(envp);
	get_prompt(&shell);
	read_command(&shell);
	while (shell.command_splited[i])
	{
		free(shell.command_splited[i]);
		i++;
	}
	free(shell.command_splited);
	free(shell.command);
	free(shell.prompt);
	free_env(shell.env);
	free_export(shell.exp);
	return (0);
}

void	read_command(t_minishell *shell)
{
	while (1)
	{
		shell->command = readline(shell->prompt);
		if (!*shell->command)
			free(shell->command);
		else
		{
			add_history(shell->command);
			if (parsing(shell))
				break ;
			wait(0);
			free(shell->command);
		}
	}
}