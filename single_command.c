/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/03 11:45:48 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	//char	*command;

	shell->command_args = remove_redirs(shell->command);
	//shell->command_args = ft_splitting(shell->command, ' ');
	//command = quote_remover(shell->command_args[0]);
	//free(shell->command_splitted[0]);
	//shell->command_args[0] = ft_strdup(command);
	//free(command);
	//handle_redirects(shell);
	if(execute_single_cmd(shell, shell->command_args[0]))
		return (1);
	get_exit_status(shell);
	free_splited(shell->command_args);
	//free_splited(shell->command_args);
	return (0);
}

char	**remove_redirs(char *command)
{
	int		i;
	char	**command_args;

	i = 0;
	command_args = ft_splitting(command, ' ');
	while(command_args[i])
	{
		if(string_comp(command_args[i], ">"))
		{
			command_args[i] = 0;
			break ;
		}
		if(string_comp(command_args[i], ">>"))
		{
			command_args[i] = 0;
			break ;
		}
		if(string_comp(command_args[i], "<"))
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
	int		num_words;
	char	**command_args;

	i = 0;
	j = 0;
	k = 0;
	num_words = countwords(command);
	command_args = (char **)malloc(sizeof(char *) * (num_words + 1));
	while(command[i])
	{
		while(command[i] == delimiter)
			i++;
		if(command[i] != delimiter)
		{
			k = i;
			while(command[k] != delimiter && command[k])
				k++;
			command_args[j] = ft_substr(command, i, k - i);
			while(command[i] != delimiter && command[i])
				i++;
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