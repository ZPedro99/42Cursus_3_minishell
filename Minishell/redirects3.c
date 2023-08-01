/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:08:25 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 12:13:51 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_sign(t_minishell *sh, int i, char **cmd_args, char *cmd)
{
	int	num_words;

	num_words = countwords(cmd);
	if (string_comp(cmd_args[i], ">>"))
	{
		handle_append(sh, i, cmd_args, cmd);
		place_null(i, num_words, cmd_args);
		return (cmd_args);
	}
	if (string_comp(cmd_args[i], "<<"))
	{
		handle_heredoc(sh, i, cmd_args, cmd);
		place_null(i, num_words, cmd_args);
		return (cmd_args);
	}
	return (cmd_args);
}

void	redirect(t_minishell *shell)
{
	dup2(shell->stdin_fd, STDIN_FILENO);
	dup2(shell->stdout_fd, STDOUT_FILENO);
}
