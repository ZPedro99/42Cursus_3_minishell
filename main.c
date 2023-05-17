/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/17 10:57:13 by jomirand         ###   ########.fr       */
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
		if(parsing(readline(shell.prompt), &shell))
			break;
	}
	/*while(shell->env != NULL)
	{
		printf("%s\n", ((t_env *)(shell->env->content))->info);
		shell->env = shell->env->next;
	}*/
	/*while(shell->exp != NULL)
	{
		printf("%s\n", ((t_env *)(shell->exp->content))->name);
		shell->exp = shell->exp->next;
	}*/
	free(shell.prompt);
	free_lists(shell.env);
	free_lists(shell.exp);
	return (0);
}
