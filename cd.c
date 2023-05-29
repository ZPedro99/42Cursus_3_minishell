/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/05/29 12:02:57 by emsoares         ###   ########.fr       */
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
		free(pwd_antigo);
		free(shell->pwd);
		chdir(getenv("HOME"));
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		free(pwd_atual);
		free(shell->pwd);
	}
	else if (string_comp(shell->command_splited[1], ".."))
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);//Vai ser o OLDPWD
		printf("antigo PWD: %s\n", pwd_antigo);
		free(pwd_antigo);
		free(shell->pwd);
		chdir("..");
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		free(pwd_atual);
		free(shell->pwd);
	}
	else
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);//Vai ser o OLDPWD
		printf("antigo PWD: %s\n", pwd_antigo);
		free(pwd_antigo);
		free(shell->pwd);
		if(chdir(shell->command_splited[1]) == -1)
		{
			printf("%s: No such file or directory\n", shell->command_splited[1]);
			return ;
		}
		shell->pwd = getcwd(0, 0);
		pwd_atual = ft_strdup(shell->pwd);
		printf("novo PWD: %s\n", pwd_atual);
		free(pwd_atual);
		free(shell->pwd);
	}
}
// se fizer cd - volta ao diretorio anterior
//falta caminho absoluto fds
