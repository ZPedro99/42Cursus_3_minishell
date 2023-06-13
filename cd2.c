/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:00:18 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/13 12:51:11 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir_home(t_minishell *shell)
{
	free(shell->pwd);
	free(shell->old_pwd);
	shell->pwd = getcwd(0, 0);
	shell->old_pwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	chdir(shell->home);
	shell->pwd = getcwd(0, 0);
	change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
}

void	change_dir_minus(t_minishell *shell)
{
	free(shell->pwd);
	shell->pwd = getcwd(0, 0);
	chdir(shell->old_pwd);
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	shell->pwd = getcwd(0, 0);
	change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
}

void	change_dir_dotdot(t_minishell *shell)
{
	free(shell->pwd);
	free(shell->old_pwd);
	shell->pwd = getcwd(0, 0);
	shell->old_pwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	chdir("..");
	shell->pwd = getcwd(0, 0);
	change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
}

void	change_dir_rest(t_minishell *shell)
{
	free(shell->pwd);
	free(shell->old_pwd);
	shell->pwd = getcwd(0, 0);
	shell->old_pwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	if (chdir(shell->command_splited[1]) == -1)
	{
		//printf("%s: No such file or directory\n", shell->command_splited[1]);
		return ;
	}
	shell->pwd = getcwd(0, 0);
	change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
	return ;
}
