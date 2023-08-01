/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:48:09 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 09:27:16 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**place_null(int i, int num_words, char **command_args)
{
	if (i == num_words - 2)
	{
		free(command_args[i]);
		free(command_args[i + 1]);
		command_args[i] = 0;
		return (command_args);
	}
	return (command_args);
}

void	handle_output(t_minishell *sh, int i, char **cmd_args, char *cmd)
{
	if (redirect_output(i, cmd_args))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(2);
	}
}

void	handle_input(t_minishell *sh, int i, char **cmd_args, char *cmd)
{
	if (redirect_input(i, cmd_args))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(2);
	}
}

void	handle_append(t_minishell *sh, int i, char **cmd_args, char *cmd)
{
	if (redirect_append(i, cmd_args))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(2);
	}
}

void	handle_heredoc(t_minishell *sh, int i, char **cmd_args, char *cmd)
{
	if (here_doc(cmd_args[i + 1]))
	{
		free_child_p(sh, cmd_args, cmd);
		exit(2);
	}
	sh->stdin_fd = open(".heredoc", O_RDONLY);
	if (sh->stdin_fd < 0)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<<'.\n", 2);
		free_child_p(sh, cmd_args, cmd);
		exit(2);
	}
}
