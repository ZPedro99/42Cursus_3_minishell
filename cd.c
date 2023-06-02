/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/06/02 11:22:21 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd(t_minishell *shell)
{
	//char	*pwd_atual;
	char	*dir_change;

	dir_change = NULL;
	if ((shell->command_splited[1] == 0) || (string_comp(shell->command_splited[1], "~")))
	{
		free(shell->pwd);
		free(shell->old_pwd);
		shell->pwd = getcwd(0, 0);
		shell->old_pwd = ft_strdup(shell->pwd);
		//printf("PWD antigo: %s\n", pwd_antigo);
		free(shell->pwd);
		//dir_change = change_dir(shell->env, "HOME=");
		chdir(shell->home);
		shell->pwd = getcwd(0, 0);
		//pwd_atual = ft_strdup(shell->pwd);
		//printf("PWD atual: %s\n", pwd_atual);
		change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
		//free(pwd_antigo);
		//free(pwd_atual);
		//free(shell->pwd);
		//free(dir_change);
		return ;
	}
	if (string_comp(shell->command_splited[1], "-"))
	{
		free(shell->pwd);
		shell->pwd = getcwd(0, 0);
		//printf("PWD antigo: %s\n", pwd_antigo);
		//free(shell->pwd);
		//dir_change = change_dir(shell->env, "OLDPWD=");
		chdir(shell->old_pwd);
		free(shell->old_pwd);
		shell->old_pwd = ft_strdup(shell->pwd);
		free(shell->pwd);
		shell->pwd = getcwd(0, 0);
		//pwd_atual = ft_strdup(shell->pwd);
		//printf("PWD atual: %s\n", pwd_atual);
		change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
		//free(pwd_antigo);
		//free(pwd_atual);
		//free(shell->pwd);
		//free(dir_change);
		return ;
	}
	else if (string_comp(shell->command_splited[1], ".."))
	{
		free(shell->pwd);
		free(shell->old_pwd);
		shell->pwd = getcwd(0, 0);
		shell->old_pwd = ft_strdup(shell->pwd);
		//printf("PWD antigo: %s\n", pwd_antigo);
		free(shell->pwd);
		chdir("..");
		shell->pwd = getcwd(0, 0);
		//pwd_atual = ft_strdup(shell->pwd);
		//printf("PWD atual: %s\n", pwd_atual);
		change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
		//free(pwd_antigo);
		//free(pwd_atual);
		//free(shell->pwd);
		return ;
	}
	else
	{
		shell->pwd = getcwd(0, 0);
		shell->old_pwd = ft_strdup(shell->pwd);
		//printf("PWD antigo: %s\n", pwd_antigo);
		free(shell->pwd);
		if (chdir(shell->command_splited[1]) == -1)
		{
			printf("%s: No such file or directory\n", shell->command_splited[1]);
			return ;
		}
		shell->pwd = getcwd(0, 0);
		//pwd_atual = ft_strdup(shell->pwd);
		//printf("PWD atual: %s\n", pwd_atual);
		change_env_and_exp(shell->env, shell->exp, shell->old_pwd, shell->pwd);
		//free(pwd_antigo);
		//free(pwd_atual);
		//free(shell->pwd);
		return ;
	}
}

void	change_env_and_exp(t_list *env, t_list *exp, char *old_pwd, char *new_pwd)
{
	t_list	*temp_env;
	t_list	*temp_exp;

	temp_env = env;
	while (!string_comp(((t_env *)(temp_env->content))->name, "PWD="))
	{
		if (temp_env->next == NULL)
			return ;
		temp_env = temp_env->next;
	}
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(new_pwd);
	temp_env = env;
	while (!string_comp(((t_env *)(temp_env->content))->name, "OLDPWD="))
	{
		if (temp_env->next == NULL)
			return ;
		temp_env = temp_env->next;
	}
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(old_pwd);
	temp_exp = exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name, "declare -x PWD="))
	{
		if (temp_exp->next == NULL)
			return ;
		temp_exp = temp_exp->next;
	}
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = join_quotes(new_pwd);
	temp_exp = exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name, "declare -x OLDPWD="))
	{
		if (temp_exp->next == NULL)
			return ;
		temp_exp = temp_exp->next;
	}
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = join_quotes(old_pwd);

}

char	*join_quotes(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 3));
	temp[0] = '\"';
	while(str[j])
	{
		temp[i] = str[j];
		i++;
		j++;
	}
	temp[i] = '\"';
	i++;
	temp[i] = '\0';
	return(temp);
}

char	*change_dir(t_list *env, char *str)
{
	t_list	*temp;

	temp = env;
	while (!string_comp(((t_env *)(temp->content))->name, str))
		temp = temp->next;
	if(temp->next == NULL)
		return (NULL);
	return (((t_env *)(temp->content))->info);
}