/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/25 11:36:13 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	char	**execute;
	int		i;
	int		argument_size;
	int		flag;
	int		j;
	int		quote_count;
	char	nl;

	execute = ft_split(shell->command, ' ');
	argument_size = (wordcount(execute)) - 1;
	if(!argument_size)
	{
		write(1, "\n", 1);
		return ;
	}
	flag = check_flag(execute[1]);
	if(flag == 0)
	{
		nl = 'n';
		i = 1;
	}
	if(flag == 1)
	{
		nl = 'y';
		i = 2;
	}
	j = 0;
	while(execute[i])
	{
		if(check_flag(execute[i]) == 1 && nl == 'y')
			i++;
		else
		{
			quote_count = counting_quote(execute[i]);
			j = 0;
			while(execute[i][j])
			{
				if((execute[i][j] == '"' || execute[i][j] == '\'') && quote_count % 2 == 0)
					j++;
				while(execute[i][j])
				{
					if((execute[i][j] == '"' || execute[i][j] == '\''))
						break;
					write(1, &execute[i][j], 1);
					j++;
				}
				if(i != argument_size)
					write(1, " ", 1);
			}
		i++;
		}
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

int	counting_quote(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
			quote_count++;
		i++;
	}
	return(quote_count);
}