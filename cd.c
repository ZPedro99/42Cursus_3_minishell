/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/05/26 17:55:36 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd(t_minishell *shell)
{
	char	*pwd_antigo;
	char	*pwd_atual;

	if(string_comp(shell->command_splited[1], ".."))
	{
		shell->pwd = getcwd(0, 0);
		pwd_antigo = ft_strdup(shell->pwd);
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
}

/* serve apenas para mudar de diretorios, ou seja
se queremos ir para um diretorio no final do nome tem de 
ter um / ex: minishell/ exam03/ cd.c(nao pode pq nao e
diretorio, logo tem de aparecer mensagem de erro) */