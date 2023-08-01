/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:38 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 12:36:07 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct_spaces(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		free(shell->paths[i]);
		i++;
	}
	free(shell->paths);
	if (shell->command)
		free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->expander_flags);
	free(shell->home);
	free_export(shell->exp);
	free_env(shell->env);
}

void	free_splited(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_copies(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	free_eof(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		free(shell->paths[i]);
		i++;
	}
	free(shell->paths);
	free(shell->command);
	free(shell->prompt);
	free(shell->pwd);
	free(shell->old_pwd);
	free(shell->home);
	free_export(shell->exp);
	free_env(shell->env);
}

int	free_child_p(t_minishell *shell, char **cmd_args, char *command)
{
	unlink(".heredoc");
	free_struct(shell);
	free(command);
	if (cmd_args[0])
		free_splited(cmd_args);
	else
		free(cmd_args);
	return (0);
}
