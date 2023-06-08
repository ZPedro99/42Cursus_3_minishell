/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/08 16:53:32 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	char	**execute;
	int		i;
	int		argument_size;
	int		j;
	int		double_quote_count;
	int		single_quote_count;
	char	ignore;
	char	nl;

	if (check_dollar_sign(shell))
		return ;
	argument_size = (wordcount(shell->command, ' ')) - 1;
	if (!argument_size)
	{
		write(1, "\n", 1);
		return ;
	}
	execute = ft_split(shell->command, ' ');
	if(execute[1][0] == '(' || execute[1][0] == ')')
	{
		ft_putstr_fd("Error: cant cope with parenthesis on first position\n", 2);
		return ;
	}
	if (!check_flag(execute[1]))
	{
		nl = 'n';
		i = 1;
	}
	if (check_flag(execute[1]))
	{
		nl = 'y';
		i = 2;
	}
	j = 0;
	while (execute[i])
	{
		if (check_flag(execute[i]) == 1 && nl == 'y')
			i++;
		else
		{
			double_quote_count = counting_quote(execute[i], '"');
			single_quote_count = counting_quote(execute[i], '\'');
			j = 0;
			while (execute[i][j])
			{
				if (execute[i][0] == '"' && double_quote_count % 2 != 0)
				{
					ft_putstr_fd("double quotes impar\n", 2);
					return ;
				}
				if (execute[i][0] == '\'' && double_quote_count % 2 != 0)
				{
					ft_putstr_fd("single quotes impar\n", 2);
					return ;
				}
				if ((execute[i][0] == '"' && execute[i][ft_strlen(execute[i]) - 1] == '"') && double_quote_count % 2 == 0)
				{
					ignore = '"';
					j++;
				}
				if ((execute[i][0] == '\'' && execute[i][ft_strlen(execute[i]) - 1] == '\'') && single_quote_count % 2 == 0)
				{
					ignore = '\'';
					j++;
				}
				while (execute[i][j])
				{
					if (execute[i][j] == '"' && double_quote_count % 2 == 0 && ignore == '"')
						break ;
					if (execute[i][j] == '\'' && single_quote_count % 2 == 0 && ignore == '\'')
						break ;
					write(1, &execute[i][j], 1);
					j++;
				}
				if (i != argument_size)
					write(1, " ", 1);
			}
		i++;
		}
	}
	i = 0;
	if (!check_flag(execute[1]))
		printf("\n");
	while (execute[i])
	{
		free(execute[i]);
		i++;
	}
	free(execute);
}

int	wordcount(char *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wordcount++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wordcount);
}

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] == '-')
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	counting_quote(char *str, char c)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == c)
			quote_count++;
		i++;
	}
	return (quote_count);
}

int	check_dollar_sign(t_minishell *shell)
{
	int	i;
	int	j;
	int	len;
	char	*name;
	t_list	*temp;

	i = 0;
	j = 0;
	while (shell->command_splited[i])
	{
		if (shell->command_splited[i][0] == '$')
		{
			name = malloc(sizeof(char) * ft_strlen(shell->command_splited[i]) + 1);
			len = ft_strlen(shell->command_splited[i]);
			while(j < (len - 1))
			{
				name[j] = shell->command_splited[i][j + 1];
				j++;
			}
			name[j] = '=';
			temp = shell->env;
			while(!string_comp(((t_env *)(temp->content))->name, name))
				temp = temp->next;
			if (!temp)
				return (0);
			printf("%s\n", ((t_env *)(temp->content))->info);
			free(name);
		}
		i++;
	}
	return (1);
}