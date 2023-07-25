/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 12:34:12 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_cd(t_minishell *shell)
{
	if (!shell->command_args[1])
	{
		change_dir_home(shell);
		return (0);
	}
	if (string_comp(shell->command_args[1], ""))
		return (0);
	if ((shell->command_args[1] == 0)
		|| (string_comp(shell->command_args[1], "~")))
	{
		change_dir_home(shell);
		return (0);
	}
	if (do_cd2(shell) == 0)
		return (0);
	return (1);
}

int	do_cd2(t_minishell *shell)
{
	if (string_comp(shell->command_args[1], "-"))
	{
		change_dir_minus(shell);
		return (0);
	}
	else if (string_comp(shell->command_args[1], ".."))
	{
		change_dir_dotdot(shell);
		return (0);
	}
	else if (string_comp(shell->command_args[1], "."))
		return (0);
	else
	{
		if (change_dir_rest(shell) == 0)
			return (0);
		return (1);
	}
	return (1);
}

void	change_env_exp(t_list *env, t_list *exp, char *o_pwd, char *n_pwd)
{
	t_list	*temp_env;

	temp_env = env;
	while (!string_comp(((t_env *)(temp_env->content))->name, "PWD="))
	{
		if (temp_env->next == NULL)
			return ;
		temp_env = temp_env->next;
	}
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(n_pwd);
	temp_env = env;
	while (!string_comp(((t_env *)(temp_env->content))->name, "OLDPWD="))
	{
		if (temp_env->next == NULL)
			return ;
		temp_env = temp_env->next;
	}
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(o_pwd);
	change_exp(exp, o_pwd, n_pwd);
}

void	change_exp(t_list *exp, char *o_pwd, char *n_pwd)
{
	t_list	*temp_exp;

	temp_exp = exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name,
		"declare -x PWD="))
	{
		if (temp_exp->next == NULL)
			return ;
		temp_exp = temp_exp->next;
	}
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = join_quotes(n_pwd);
	temp_exp = exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name,
		"declare -x OLDPWD="))
	{
		if (temp_exp->next == NULL)
			return ;
		temp_exp = temp_exp->next;
	}
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = join_quotes(o_pwd);
}

char	*change_dir(t_list *env, char *str)
{
	t_list	*temp;

	temp = env;
	while (!string_comp(((t_env *)(temp->content))->name, str))
		temp = temp->next;
	if (temp->next == NULL)
		return (NULL);
	return (((t_env *)(temp->content))->info);
}
