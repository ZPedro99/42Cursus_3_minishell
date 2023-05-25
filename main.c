/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/25 17:42:36 by emsoares         ###   ########.fr       */
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
	while(1)
	{
		shell.command = readline(shell.prompt);
		if(!*shell.command)
			free(shell.command);
		else
		{
		add_history(shell.command);
		if(parsing(&shell))
			break;
		wait(0);
		free(shell.command);
		}
	}
	while(shell.command_splited[i])
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
