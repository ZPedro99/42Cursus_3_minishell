/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/13 22:52:54 by emsoares         ###   ########.fr       */
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
	flag = print_echo2(shell, word_num, ret);
	if (!flag)
		printf("\n");
	if (flag == 1)
		return ;
}

int	print_echo2(t_minishell *shell, int word_num, int ret)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	while (shell->command_splited[i])
	{
		if (shell->command_splited[i][0] == '$')
		{
			if (ft_echo_es(shell, i) == 0)
				return (0);
			ret = check_dollar_sign(shell->command_splited[i], shell);
			if (ret == 1 || !ret)
				i++;
		}
		else
		{
			flag = print_normal_words(shell->command_splited[i]);
			i++;
		}
		if (i < word_num && !string_comp(shell->command_splited[i - 1], "-n"))
			printf(" ");
	}
	return (flag);
}

int	print_normal_words(char *str)
{
	static int	flag;
	int			double_quote_count;
	int			single_quote_count;

	if (str[0] == '(' || str[0] == ')')
		return (ft_putstr_fd("Error: cant cope with parenthesis on first position\n", 2), 1);
	if (string_comp(str, "-n"))
	{
		flag = 1;
		return (1);
	}
	double_quote_count = counting_quote(str, '"');
	single_quote_count = counting_quote(str, '\'');
	if (check_pairs(str, double_quote_count, '"'))
		return (2);
	if (check_pairs(str, single_quote_count, '\''))
		return (2);
	if (print_trimmed_string(str, double_quote_count, '"', flag))
		return (flag);
	if (print_trimmed_string(str, single_quote_count, '\'', flag))
		return (flag);
	printf("%s", str);
	return (flag);
}

int	check_pairs(char *str, int q_count, char q_type)
{
	if (str[0] == q_type && str[ft_strlen(str) - 1]
		!= q_type && q_count % 2 != 0)
	{
		if (q_type == '"' )
			ft_putstr_fd("double quotes impar\n", 2);
		else if (q_type == '\'' )
			ft_putstr_fd("single quotes impar\n", 2);
		return (1);
	}
	return (0);
}

int	print_trimmed_string(char *str, int quote_count, char quote_type, int flag)
{
	char	*print;
	char	ignore;
	char	cast_qtype[2];

	cast_qtype[0] = quote_type;
	cast_qtype[1] = '\0';
	if ((str[0] == quote_type && str[ft_strlen(str) - 1] == quote_type)
		&& quote_count % 2 == 0)
		ignore = quote_type;
	if (quote_count % 2 == 0 && ignore == quote_type)
	{
		print = ft_strtrim(str, cast_qtype);
		printf("%s", print);
		free(print);
		return (flag);
	}
	return (0);
}

/* int	print_normal_words(char *str)
{
	static int	flag;
	int			c;
	int			double_quote_count;
	int			single_quote_count;
	char		ignore;
	char		*print;

	if (str[0] == '(' || str[0] == ')')
	{
		ft_putstr_fd("Error: cant cope with parenthesis on first position\n", 2);
		return (1);
	}
	if (string_comp(str, "-n"))
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
	return (flag);
} */