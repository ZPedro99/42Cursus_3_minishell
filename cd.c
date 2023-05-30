/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/05/30 11:17:45 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd(t_minishell *shell)
{
	char	*pwd_antigo;
	char	*pwd_atual;

	if ((shell->command_splited[1] == 0) || (string_comp(shell->command_splited[1], "~")))
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);//Vai ser o OLDPWD
		printf("antigo PWD: %s\n", pwd_antigo);
		free(shell->pwd);
		chdir(getenv("HOME"));
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		change_env(shell->env, pwd_antigo, pwd_atual);
		free(pwd_antigo);
		free(pwd_atual);
		free(shell->pwd);
	}
	else if (string_comp(shell->command_splited[1], ".."))
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);//Vai ser o OLDPWD
		printf("antigo PWD: %s\n", pwd_antigo);
		free(shell->pwd);
		chdir("..");
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		change_env(shell->env, pwd_antigo, pwd_atual);
		free(pwd_antigo);
		free(pwd_atual);
		free(shell->pwd);
	}
	else
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);//Vai ser o OLDPWD
		printf("antigo PWD: %s\n", pwd_antigo);
		free(shell->pwd);
		if(chdir(shell->command_splited[1]) == -1)
		{
			printf("%s: No such file or directory\n", shell->command_splited[1]);
			return ;
		}
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		change_env(shell->env, pwd_antigo, pwd_atual);
		free(pwd_antigo);
		free(pwd_atual);
		free(shell->pwd);
	}
}
// se fizer cd - volta ao diretorio anterior
//falta caminho absoluto fds

void	change_env(t_list *env, char *old_pwd, char *new_pwd)
{
	t_list	*temp;

	temp = env;
	while(!string_comp(((t_env *)(temp->content))->name, "PWD="))
		temp = temp->next;
	free(((t_env *)(temp->content))->info);
	((t_env *)(temp->content))->info = ft_strdup(new_pwd);
	temp = env;
	while(!string_comp(((t_env *)(temp->content))->name, "OLDPWD="))
		temp = temp->next;
	free(((t_env *)(temp->content))->info);
	((t_env *)(temp->content))->info = ft_strdup(old_pwd);
}