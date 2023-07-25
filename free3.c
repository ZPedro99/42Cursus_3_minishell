/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:40:20 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 11:34:38 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_child_process_multi(t_minishell *shell, char *command)
{
	unlink(".heredoc");
	free_struct_multi(shell);
	free_splited(shell->command_args);
	free(command);
	free_splited(shell->command_splitted_pipe);
	return (0);
}
