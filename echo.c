/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/10 14:20:10 by jomirand         ###   ########.fr       */
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
		//write(1, "\n", 1);
		printf("\n");
	if (flag == 1)
		return ;
}

int	print_echo2(t_minishell *shell, int word_num, int ret)
{
	int	flag;
	int	i;
	int	j;
	//char	*new_str;

	(void)ret;
	i = 1;
	flag = 0;
	while (shell->command_args[i])
	{
		j = i;
		if(check_redirect(shell->command_args[i]))
			break ;
		/* if (shell->command_args[i][0] == '$')
		{
			ft_echo_es(shell, i);
			ret = check_dollar_sign(shell->command_args[i], shell);
			if (ret == 1 || !ret)
				i++;
		} */
		if(i == 1 && string_comp(shell->command_args[i], "-n"))
		{
			flag = 1;
			i++;
			j++;
		}
		/* while(shell->command_args[i])
		{
			if(check_closed_quotes(shell->command_args[i]) == 1)
			{
				write(2, "Error", 5);
				return (0);
			}
			i++;
		}
		i = j;
		new_str = quote_remover(shell->command_args[i]);
		if(!new_str)
			return (0); */
		//handle_quotes(shell->command_args[i]);
		if(!shell->command_args[i])
			return(flag);
		printf("%s", shell->command_args[i]);
		//free(new_str);
		i++;
		if (i < word_num)
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
	return(quote);
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
	flag = 1;
	ignore = 0;
	while(str[i])
	{
		if(str[i] == '"' && ignore == 0)
			ignore = '"';
		else if(str[i] == '\'' && ignore == 0)
			ignore = '\'';
		else if(str[i] == ignore)
		{
			if(flag == 2 && str[i] == ignore)
			{
				flag = 1;
				ignore = 0;
				i++;
			}
			if(str[i] && flag == 1 && str[i] == ignore)
			{
				flag = 2;
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

int	check_redirect(char *str)
{
	if(string_comp(str, ">"))
		return (1);
	if(string_comp(str, "<"))
		return (1);
	if(string_comp(str, ">>"))
		return (1);
	if(string_comp(str, "<<"))
		return (1);
	return (0);
}

char	*quotes_middle(char *str, int num_quotes)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - num_quotes + 1));
	while(str[i])
	{
		while(str[i] == '"' || str[i] == '\'')
			i++;
		if(str[i] == '\0')
			break ;
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return(new_str);
}