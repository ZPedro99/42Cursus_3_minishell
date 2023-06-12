/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/12 12:44:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	int		ret;
	int		i;
	int		flag;
	int		word_num;

	i = 1;
	word_num = wordcount(shell->command, ' ');
	while(shell->command_splited[i])
	{
		if(shell->command_splited[i][0] == '$')
		{
			ret = check_dollar_sign(shell->command_splited[i], shell);
			if(ret == 1)
				i++;
			if(!ret)
				i++;
		}
		else
		{
			flag = print_normal_words(shell->command_splited[i]);
			i++;
		}
		if(i < word_num && !string_comp(shell->command_splited[i - 1], "-n"))
			printf(" ");
	}
	if(!flag)
		printf("\n");
	if(flag == 1)
		return ;
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

int	check_dollar_sign(char *str, t_minishell *shell)
{
	int	i;
	int	j;
	int	len;
	char	*name;
	t_list	*temp;

	i = 0;
	j = 0;
	name = malloc(sizeof(char) * ft_strlen(str) + 1);
	len = ft_strlen(str);
	while(j < (len - 1))
	{
		name[j] = str[j + 1];
		j++;
	}
	name[j] = '=';
	temp = shell->env;
	while(temp != NULL)
	{
		if(string_comp(((t_env *)(temp->content))->name, name))
		{
			printf("%s", ((t_env *)(temp->content))->info);
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	if (!temp)
	{
		free(name);
		return (0);
	}
	free(name);
	return (0);
}

int	print_normal_words(char *str)
{
	static int	flag;
	int		c;
	int		double_quote_count;
	int		single_quote_count;
	char	ignore;
	char	*print;

	if(str[0] == '(' || str[0] == ')')
	{
		ft_putstr_fd("Error: cant cope with parenthesis on first position\n", 2);
		return (1);
	}
	if(string_comp(str, "-n"))
	{
		flag = 1;
		return (1);
	}
	c = 0;
	double_quote_count = counting_quote(str, '"');
	single_quote_count = counting_quote(str, '\'');
	ignore = 0;
	if (str[c] == '"' && double_quote_count % 2 != 0)
	{
		ft_putstr_fd("double quotes impar", 2);
		return (2);
	}
	if (str[c] == '\'' && single_quote_count % 2 != 0)
	{
		ft_putstr_fd("single quotes impar", 2);
		return (2);
	}
	if ((str[c] == '"' && str[ft_strlen(str) - 1] == '"') && double_quote_count % 2 == 0)
		ignore = '"';
	if ((str[c] == '\'' && str[ft_strlen(str) - 1] == '\'') && single_quote_count % 2 == 0)
		ignore = '\'';
	if (double_quote_count % 2 == 0 && ignore == '"')
	{
		print = ft_strtrim(str, "\"");
		printf("%s", print);
		free(print);
		return (flag);
	}
	if (single_quote_count % 2 == 0 && ignore == '\'')
	{
		print = ft_strtrim(str, "'");
		printf("%s", print);
		free(print);
		return (flag);
	}
	printf("%s", str);
	return(flag);
}