/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/24 15:22:49 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	char	**execute;
	int		i;
	int		argument_size;
	int		flag;

	execute = ft_split(shell->command, ' ');
	flag = check_flag(execute[1]);
	if(flag == 0)
		i = 1;
	if(flag == 1)
		i = 2;
	argument_size = (wordcount(execute)) - 1;
	while(execute[i])
	{
		printf("%s", execute[i]);
		if(i != argument_size)
			printf(" ");
		i++;
	}
	i = 0;
	while(execute[i])
	{
		free(execute[i]);
		i++;
	}
	free(execute);
	if(flag == 0)
		printf("\n");
}

int	wordcount(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	if(flag[0] == '-')
	{
		while(flag[i])
		{
			if(flag[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}