/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:28:51 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/13 22:28:51 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_es(t_minishell *shell, int i)
{
	char	*str;

	str = ft_strtrim(shell->command_splitted[i], "$?");
	if (shell->command_splitted[i][1] == '?')
	{
		printf("%d%s", g_exit_status, str);
		free(str);
		return (0);
	}
	free (str);
	return (1);
}
