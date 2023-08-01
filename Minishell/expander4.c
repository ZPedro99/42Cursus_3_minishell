/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:27:11 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 17:35:42 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_vars(t_minishell *shell, char *initial_str, char *rest_str)
{
	char		*temp;
	char		*return_str;

	return_str = 0;
	temp = ft_strdup(initial_str);
	free(initial_str);
	if (shell->expander_flag == 0)
		return_str = ft_strjoin("", temp);
	else
	{
		return_str = ft_strjoin(rest_str, temp);
		free(rest_str);
	}
	shell->expander_flag++;
	free(temp);
	if (shell->expander_flag == (ft_wordcount_meta(shell->command, '$') - 1))
		shell->expander_flag = 0;
	return (return_str);
}

int	obtain_end(t_minishell *sh, int i, int *st)
{
	while (sh->command_args[i][*st] != '$' && sh->command_args[i][*st])
		(*st)++;
	if (sh->command_args[i][*st] != '\0')
		(*st)++;
	return (*st);
}

void	expand_multiple_end(t_minishell *sh, int i, char *return_str)
{
	free(sh->command_args[i]);
	sh->command_args[i] = ft_strdup(return_str);
	free(return_str);
}
