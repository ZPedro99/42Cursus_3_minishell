/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/16 11:43:48 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	int	i;
	char	*line;
	i = 0;

	shell = malloc(sizeof(t_minishell));
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("invalid number of arguments!", 2);
		return (1);
	}
	shell->env = get_env_vars(envp);
	shell->prompt = print_prompt(envp, shell);
	line = readline(shell->prompt);
	puts(line);
	//shell->export = get_exp_vars()
	/*while(shell->env != NULL)
	{
		puts(shell->env->content);
		shell->env = shell->env->next;
	}*/
	return (0);
}
