/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/23 15:05:40 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

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
		add_history(shell.command);
		if(parsing(&shell))
			break;
		wait(0);
		free(shell.command);
	}
	free(shell.prompt);
	free_lists(shell.env);
	free_lists(shell.exp);
	shell.exp = NULL; // Set shell.exp to NULL to avoid double-freeing
	return (0);
}
