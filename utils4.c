/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:44:29 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 11:53:51 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_args(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->command_args[i])
		i++;
	if (i == 1)
		print_exp(shell);
	else if (i > 1)
		return ;
}
