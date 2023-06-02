/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/02 11:19:05 by jomirand         ###   ########.fr       */
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
	obtain_vars(&shell);
	get_prompt(&shell);
	read_command(&shell);
	free_struct(&shell);
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

void	obtain_vars(t_minishell *shell)
{
	t_list *temp;

	temp = shell->env;
	while (temp)
	{
		if (string_comp(((t_env *)(temp->content))->name, "PWD="))
			shell->pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "OLDPWD="))
			shell->old_pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "HOME="))
			shell->home = ft_strdup(((t_env *)(temp->content))->info);
		temp = temp->next;
	}
}