/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:44:43 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 16:13:26 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	countwords(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
					break ;
				i++;
			}
		}
		while (str[i] == ' ')
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
