/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:45:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/26 15:45:36 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if ((str[i] == '\'' || str[i] == '"') && quote == str[i])
			quote = 0;
		if (!quote && (str[i] == '>' || str[i] == '<'))
			new_str = whitespaces2(new_str, str, &i, &j);
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*whitespaces2(char *new_str, char *str, int *i, int *j)
{
	new_str[*j] = ' ';
	(*j)++;
	new_str[*j] = str[*i];
	(*j)++;
	(*i)++;
	if (str[*i] == str[*i - 1])
	{
		new_str[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	new_str[*j] = str[*i];
	(*j)++;
	(*i)++;
	return (new_str);
}

int	strlength(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			len += 3;
			i++;
		}
		len++;
		i++;
	}
	return (len);
}

int	check_quotes_on_args(char **args, t_minishell *shell)
{
	int		i;
	char	*unquoted_cmd;

	i = -1;
	while (args[++i])
	{
		if (ft_strrchr(args[i], '\'') || ft_strrchr(args[i], '"'))
		{
			if (check_closed_quotes(args[i]) == 1)
			{
				ft_putstr_fd("Minishell: unclosed quotes.\n", 2);
				return (1);
			}
			if (check_closed_quotes(args[i]) == 0)
			{
				if (ft_search(args[i], '$') == 1)
					quote_on_expander(args[i], i, shell);
				unquoted_cmd = quote_remover(args[i]);
				free(args[i]);
				args[i] = ft_strdup(unquoted_cmd);
				free(unquoted_cmd);
			}
		}
	}
	return (0);
}

void	quote_on_expander(char *arg, int i, t_minishell *shell)
{
	int	y;

	y = 0;
	while (arg[y] != '$')
		y++;
	if (arg[y + 1] == '\'' || arg[y + 1] == '"')
		shell->expander_flags[i] = 1;
	else if (arg[y - 1] == '\'' )
		shell->expander_flags[i] = 2;
}
