/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/15 16:48:36 by jomirand         ###   ########.fr       */
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
		write(1, "\n", 1);
	if (flag == 1)
		return ;
}

int	print_echo2(t_minishell *shell, int word_num, int ret)
{
	int	flag;
	int	i;
	int	j;
	char	*new_str;

	i = 1;
	flag = 0;
	while (shell->command_splited[i])
	{
		j = i;
		if (shell->command_splited[i][0] == '$')
		{
			ft_echo_es(shell, i);
			ret = check_dollar_sign(shell->command_splited[i], shell);
			if (ret == 1 || !ret)
				i++;
		}
		else
		{
			if(i == 1 && string_comp(shell->command_splited[i], "-n"))
			{
				flag = 1;
				i++;
			}
			while(shell->command_splited[i])
			{
				if(check_closed_quotes(shell->command_splited[i]))
				{
					write(1, "Error", 5);
					return (0);
				}
				i++;
			}
			i = j;
			new_str = quote_remover(shell->command_splited[i]);
			if(!new_str)
				return (0);
			handle_quotes(new_str);
			/* if(string_comp(new_str, shell->command_splited[i]))
				free(new_str); */
			//break ;
			/* if(!check_quote_pairs(new_str))
				perror("minishell"); */
			//flag = print_normal_words(shell->command_splited[i]);
			free(new_str);
			i++;
		}
		if (i < word_num)
			write(1, " ", 1);
	}
	return (flag);
}

/* int	print_normal_words(char *str)
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
} */

char	*quote_remover(char *str)
{
	int		i;
	int		j;
	int		len;
	int		quote_counter;
	char	*new_str;

	i = 0;
	j = 0;
	quote_counter = 0;
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len - 2 + 1));
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
			quote_counter++;
		i++;
	}
	i = 0;
	if(quote_counter == 2 && str[i] == '"' && str[len - 1] == '"')
	{
		while(str[i])
		{
			if(i == 0 || i == len - 1)
				i++;
			if(i == len)
				break;
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	if(quote_counter == 2 && str[i] == '\'' && str[len - 1] == '\'')
	{
		while(str[i])
		{
			if(i == 0 || i == len - 1)
				i++;
			if(i == len)
				break;
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	if(quote_counter == 2 && str[i] == '"' && str[len - 1] == '\'')
	{
		printf("error on quotes");
		return(0);
	}
	if(quote_counter == 2 && str[i] == '\'' && str[len - 1] == '"')
	{
		printf("error on quotes");
		return(0);
	}
	else
		return(str);
	return(new_str);
}

void	handle_quotes(char *str)
{
	int		i;
	int		flag;
	int		hold;
	int		temp;
	char	ignore;

	i = 0;
	flag = 0;
	ignore = 0;
	hold = 0;
	/* if(check_closed_quotes(str))
	{
		printf("unclosed quotes!");
		return ;
	} */
	/* while(str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			ft_putstr_fd("Error: cant cope with parenthesis on first position\n", 2);
			return ;
		}
		i++;
	} */
	i = 0;
	while(str[i])
	{
		if(str[i] == '"' && ignore == 0)
			ignore = '"';
		if(str[i] == '\'' && ignore == 0)
			ignore = '\'';
		if(str[i] == ignore)
		{
			if(flag)
			{
				flag = 0;
				temp = i;
				i = hold + 1;
				hold = temp;
				//print_string(str, i, hold);
				while(i < hold)
				{
					write(1, &str[i], 1);
					i++;
				}
				ignore = 0;
				i++;
				if(str[i] == '\0')
					return ;
			}
			if(!flag && str[i] == ignore)
			{
				hold = i;
				flag = 1;
				i++;
			}
		}
		else if (!ignore)
		{
			write(1, &str[i], 1);
			i++;
		}
		else
			i++;
	}
}

int	check_closed_quotes(char *str)
{
	int		i;
	int		flag;
	char	ignore;

	i = 0;
	flag = 0;
	ignore = 0;
	while(str[i])
	{
		if(str[i] == '"' && ignore == 0)
			ignore = '"';
		else if(str[i] == '\'' && ignore == 0)
			ignore = '\'';
		else if(str[i] == ignore)
		{
			if(flag && str[i] == ignore)
			{
				flag = 0;
				ignore = 0;
				i++;
			}
			if(str[i] && !flag && str[i] == ignore)
			{
				flag = 1;
				i++;
			}
		}
		else if(flag == 0 && (str[i] == ')' || str[i] == '('))
			return (1);
		else
			i++;
	}
	return(flag);
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