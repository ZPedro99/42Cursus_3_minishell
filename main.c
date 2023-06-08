/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/08 17:15:11 by emsoares         ###   ########.fr       */
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
	rl_clear_history();
	shell.env = get_env_vars(envp);
	shell.exp = get_exp_vars(envp);
	obtain_vars(&shell);
	get_prompt(&shell);
	read_command(&shell);
	free_struct(&shell);
	return (0);
}

void	obtain_vars(t_minishell *shell)
{
	t_list	*temp;

	temp = shell->env;
	while (temp)
	{
		if (string_comp(((t_env *)(temp->content))->name, "PWD="))
			shell->pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "OLDPWD="))
			shell->old_pwd = ft_strdup(((t_env *)(temp->content))->info);
		if (string_comp(((t_env *)(temp->content))->name, "HOME="))
			shell->home = ft_strdup(((t_env *)(temp->content))->info);
		/* if (string_comp(((t_env *)(temp->content))->name, "PATH="))
			shell->paths = save_paths(((t_env *)(temp->content))); */
		temp = temp->next;
	}
}

void	get_prompt(t_minishell *shell)
{
	char	*username;
	char	*seat;
	char	*temp;
	int		i;
	int		j;

	username = getenv("USER");
	temp = getenv("SESSION_MANAGER");
	i = 0;
	while (temp[i] != '/')
		i++;
	i++;
	j = i;
	while (temp[j] != '.')
		j++;
	seat = get_prompt2(i, j, temp);
	shell->prompt = ft_strjoin(username, seat);
	free(seat);
}

char	*get_prompt2(int i, int j, char *temp)
{
	char	*seat;

	seat = malloc(sizeof(char) * (j - i) + 4);
	j = 1;
	seat[0] = '@';
	while (temp[i] != '.')
	{
		seat[j] = temp[i];
		i++;
		j++;
	}
	seat[j] = '>';
	j++;
	seat[j] = ' ';
	j++;
	seat[j] = '\0';
	return (seat);
}

void	read_command(t_minishell *shell)
{
	while (1)
	{
		handle_signals();
		shell->command = readline(shell->prompt);
		if (!shell->command)
		{
			printf("exit\n");
			exit (0);
		}
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
	rl_clear_history();
}
