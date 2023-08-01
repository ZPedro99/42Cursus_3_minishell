/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/14 17:18:30 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell)
{
	int		flag;
	int		word_num;
	int		ret;

	ret = 0;
	word_num = wordcount(shell->command, ' ');
	if (word_num == 1)
	{
		printf("\n");
		return ;
	}
	flag = print_echo2(shell);
	if (!flag)
		printf("\n");
	if (flag == 1)
		return ;
}

int	print_echo2(t_minishell *shell)
{
	int	flag;
	int	i;
	int	j;

	if (echo_no_args(shell) == 1)
		return (1);
	i = check_no_newline_flag(shell);
	if (i == 1)
		flag = 0;
	else
		flag = 1;
	while (shell->command_args[i])
	{
		j = i;
		if (check_redirect(shell->command_args[i]))
			break ;
		if (!shell->command_args[i])
			return (flag);
		printf("%s", shell->command_args[i]);
		i++;
		if (string_comp(shell->command_args[i - 1], "") == 0)
			printf(" ");
	}
	return (flag);
}

static int	length_no_quotes(char *str)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
		{
			quote = str[i];
			len--;
		}
		else if ((str[i] == '"' || str[i] == '\'') && quote == str[i])
		{
			len--;
			quote = 0;
		}
		len++;
		i++;
	}
	return (len);
}

char	quote_checker(char *str, int i, char quote)
{
	if (ft_strrchr("\"\'", str[i]) && !quote)
		quote = str[i];
	else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
		quote = 0;
	return (quote);
}

char	*quote_remover(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	if (length_no_quotes(str) <= 0)
		return (ft_strdup(""));
	new_str = (char *)malloc(sizeof(char) * (length_no_quotes(str) + 1));
	while (str[i])
	{
		quote = quote_checker(str, i, quote);
		if (i > (int)ft_strlen(str) - 1)
			break ;
		if ((quote && quote != str[i]) || (!quote && !ft_strchr("\"\'", str[i])))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
