/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:58:53 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/08 14:19:42 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(t_minishell *shell)
{
	free (shell->pwd);
	shell->pwd = getcwd(0, 0);
	printf("%s\n", shell->pwd);
}

/* -When buf is NULL (or 0), and size is 0, getcwd returns
the size of the buffer required to store the current
working directory path, without actually modifying any memory.
-getcwd(0, 0) is used to determine the size of the buffer needed
to store the current working directory path.
It assigns the path to shell->pwd
using dynamic memory allocation
(getcwd will allocate the memory internally), prints the path
 using printf, and then frees the allocated memory with free(shell->pwd). */