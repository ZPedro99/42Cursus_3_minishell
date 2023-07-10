/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/10 15:52:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	int		i;
	char	*command;

	command = whitespaces(shell->command);
	i = 0;
	while(command[i])
	{
		if(command[i] == ' ' || command[i] == '\t')
			i++;
		else
			break;
	}
	if(i == (int)ft_strlen(command))
	{
		free(command);
		return(0);
	}
	shell->command_args = remove_redirs(command);
	if(!shell->command_args)
	{
		ft_putstr_fd("Minishell: invalid command.\n", 2);
		free(command);
		return(0);
	}
	ft_expander(shell);
	i = 0;
	if(check_quotes_on_args(shell->command_args))
		return (0);
	if(execute_single_cmd(shell, command))
	{
		free_splited(shell->command_args);
		return (1);
	}
	get_exit_status(shell);
	if(!string_comp(shell->command_args[0], "exit"))
		free(command);
	free_splited(shell->command_args);
	return (0);
}

char	**remove_redirs(char *command)
{
	int		i;
	int		num_words;
	char	**command_args;

	num_words = countwords(command);
	command_args = ft_splitting(command, ' ');
	i = 0;
	while(command_args[i])
	{
		if(check_closed_quotes(command_args[i]) == 2)
		{
			free_splited(command_args);
			return (0);
		}
		if(string_comp(command_args[i], ">"))
		{
			command_args[i] = 0;
			break ;
		}
		if(string_comp(command_args[i], ">>"))
		{
			if(i == 1)
			{
				free(command_args[i]);
				free(command_args[i + 1]);
				command_args[i] = 0;
				return(command_args);
			}
			//break ;
		}
		if(string_comp(command_args[i], "<"))
		{
			command_args[i] = 0;
			break ;
		}
		if(string_comp(command_args[i], "<<"))
		{
			command_args[i] = 0;
			break ;
		}
		i++;
	}
	return (command_args);
}

char	**ft_splitting(char *command, char delimiter)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		num_words;
	char	**command_args;
	char	ignore;
	int		flag;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	flag = 0;
	num_words = countwords(command);
	command_args = (char **)malloc(sizeof(char *) * (num_words + 1));
	while(command[i])
	{
		while(command[i] == delimiter)
			i++;
		if(!command[i])
			break ;
		if(command[i] != delimiter)
		{
			flag = 0;
			if(command[i] == '"' || command[i] == '\'')
			{
				if(command[i] == '"')
					ignore = '"';
				if(command[i] == '\'')
					ignore = '\'';
				k = i;
				k++;
				while(command[k] != ignore && command[k])
					k++;
				if(command[k] == ignore && flag == 0)
					k++;
				while(command[k] != ignore && command[k] != delimiter && command[k])
					k++;
				command_args[j] = ft_substr(command, i, k - i);
				i = k;
				/* if(command[k + 1] == '\0')
				{
					command_args[j + 1] = 0;
					return (command_args);
				} */
			}
			else
			{
				l = 0;
				k = i;
				while(command[k] != delimiter && command[k])
					k++;
				command_args[j] = ft_substr(command, i, k - i);
				/* while(i < k)
				{
					command_args[j][l] = command[i];
					i++;
					l++;
				} */
				while(command[i] != delimiter && command[i])
					i++;
			}
			//k++;
		}
		j++;
	}
	command_args[j] = 0;
	return (command_args);
}

int	countwords(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] != ' ')
		{
			count++;
			/* if(str[i] == '\0')
				break ; */
			while(str[i] != ' ')
			{
				if(str[i] == '\0')
					break ;
				i++;
			}
		}
		while(str[i] == ' ')
			i++;
	}
	return (count);
}

char	*whitespaces(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	new_str = (char *)malloc(sizeof(char) * (strlength(str) + 1));
	while(str[i])
	{
		if((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if((str[i] == '\'' || str[i] == '"') && quote == str[i])
			quote = 0;
		if(!quote && (str[i] == '>' || str[i] == '<'))
		{
			new_str[j] = ' ';
			j++;
			new_str[j] = str[i];
			j++;
			i++;
			if(str[i] == str[i - 1])
			{
				new_str[j] = str[i];
				j++;
				i++;
			}
			new_str[j] = str[i];
			j++;
			i++;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int		strlength(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if(!str)
		return(0);
	while(str[i])
	{
		if(str[i] == '<' || str[i] == '>')
		{
			len += 3;
			i++;
			//continue ;
		}
		len++;
		i++;
	}
	return(len);
}

int	check_quotes_on_args(char **args)
{
	int		i;
	char	*unquoted_cmd;

	i = 0;
	while(args[i])
	{
		if(check_closed_quotes(args[i]) == 2)
		{
			ft_putstr_fd("Minishell: unclosed quotes.\n", 2);
			return (1);
		}
		if(check_closed_quotes(args[i]) == 1)
		{
			unquoted_cmd = quote_remover(args[i]);
			free(args[i]);
			args[i] = ft_strdup(unquoted_cmd);
			free(unquoted_cmd);
		}
		i++;
	}
	return(0);
}
