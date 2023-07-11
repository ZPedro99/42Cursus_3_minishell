/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/11 14:05:55 by jomirand         ###   ########.fr       */
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
	shell->command_args = remove_redirs(command, shell);
	if(!shell->command_args)
	{
		ft_putstr_fd("Minishell: invalid command.\n", 2);
		free(command);
		return(0);
	}
	i = 0;
	if(check_quotes_on_args(shell->command_args))
		return (0);
	ft_expander(shell);
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

char	**remove_redirs(char *command, t_minishell *shell)
{
	int		i;
	int		num_words;
	char	**command_args;

	num_words = countwords(command);
	shell->expander_flags = ft_calloc(num_words, sizeof(int));
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

static int	ft_wordlen(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((str[i] && (str[i] != c)) || (str[i] && quote))
	{
		quote = quote_value(str[i], quote);
		i++;
	}
	return (i);
}
static char	*get_word(char *s, char c, char **words)
{
	char	quote;

	quote = 0;
	*words = ft_substr(s, 0, ft_wordlen(s, c));
	while ((*s && *s != c) || (*s && quote))
	{
		quote = quote_value(*s, quote);
		s++;
	}
	return (s);
}
char	**ft_splitting(char *command, char delimiter)
{
	char	**words;
	int		wdcount;
	int		j;

	j = 0;
	if (!command)
		return (0);
	wdcount = ft_wordcount_meta(command, delimiter);
	words = (char **)malloc(sizeof(char *) * (wdcount + 1));
	if (!words)
		return (0);
	while (*command)
	{
		while (*command && *command == delimiter)
			command++;
		if (*command)
			command = get_word(command, delimiter, &words[j++]);
	}
	words[j] = 0;
	return (words);
}

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
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
int	ft_wordcount_meta(char *str, char c)
{
	int		i;
	int		wordcount;
	char	quote;

	i = 0;
	wordcount = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wordcount++;
		while ((str[i] && str[i] != c) || (str[i] && quote))
		{
			quote = quote_value(str[i], quote);
			i++;
		}
	}
	return (wordcount);
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
		if(ft_strrchr(args[i], '\'') || ft_strrchr(args[i], '"'))
		{
			if(check_closed_quotes(args[i]) == 1)
			{
				ft_putstr_fd("Minishell: unclosed quotes.\n", 2);
				return (1);
			}
			if(check_closed_quotes(args[i]) == 0)
			{
				unquoted_cmd = quote_remover(args[i]);
				free(args[i]);
				args[i] = ft_strdup(unquoted_cmd);
				free(unquoted_cmd);
			}
		}
		i++;
	}
	return(0);
}
