/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:21:56 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/05 14:34:57 by jomirand         ###   ########.fr       */
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
	char	*new_str;

	i = 1;
	flag = 0;
	while (shell->command_args[i])
	{
		j = i;
		if(check_redirect(shell->command_args[i]))
			break ;
		if (shell->command_args[i][0] == '$')
		{
			ft_echo_es(shell, i);
			ret = check_dollar_sign(shell->command_args[i], shell);
			if (ret == 1 || !ret)
				i++;
		}
		else
		{
			if(i == 1 && string_comp(shell->command_args[i], "-n"))
			{
				flag = 1;
				i++;
				j++;
			}
			while(shell->command_args[i])
			{
				if(check_closed_quotes(shell->command_args[i]))
				{
					write(2, "Error", 5);
					return (0);
				}
				i++;
			}
			i = j;
			new_str = quote_remover(shell->command_args[i]);
			if(!new_str)
				return (0);
			handle_quotes(new_str);
			//free(new_str);
			i++;
		}
		if (i < word_num)
			write(1, " ", 1);
	}
	return (flag);
}

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
		return(new_str);
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
		return(new_str);
	}
	if(quote_counter == 2 && str[i] == '"' && str[len - 1] == '\'')
	{
		printf("error on quotes");
		free(new_str);
		return(0);
	}
	if(quote_counter == 2 && str[i] == '\'' && str[len - 1] == '"')
	{
		printf("error on quotes");
		free(new_str);
		return(0);
	}
	free(new_str);
	return(str);
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
				flag = 2;
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