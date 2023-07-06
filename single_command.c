/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:49:12 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/06 14:48:13 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_command(t_minishell *shell)
{
	int		i;
	char	*cmd_no_quotes;
	char	*arg_no_quotes;

	i = 0;
	if(check_closed_quotes(shell->command))
	{
		cmd_no_quotes = quote_remover(shell->command);//criar outra quote remover para o comando geral(ideia: split pelo espaco e remover a cada arg)
		free(shell->command);
		shell->command = ft_strdup(cmd_no_quotes);
		free(cmd_no_quotes);
	}
	if(shell->command[0] == ' ')
	{
		while(shell->command[i] == ' ' && shell->command[i])
		{
			if(shell->command[i] != ' ' && shell->command[i] != '\0')
				break ;
			i++;
			if(shell->command[i] == '\0')
				return (0);
		}
	}
	shell->command_args = remove_redirs(shell->command);
	//free(cmd_no_quotes);
	if(!shell->command_args)
	{
		ft_putstr_fd("Error: unclosed quotes\n", 2);
		//free_splited(shell->command_args);
		return(0);
	}
	i = 0;
	//cmd_no_quotes = 0;
	while(shell->command_args[i])
	{
		if(check_closed_quotes(shell->command_args[i]) == 1)
		{
			ft_putstr_fd("Error: unclosed quotes\n", 2);
			free_splited(shell->command_args);
			return(0);
		}
		if(check_closed_quotes(shell->command_args[i]) == 2)
		{
			arg_no_quotes = quote_remover(shell->command_args[i]);
			free(shell->command_args[i]);
			shell->command_args[i] = ft_strdup(arg_no_quotes);
			free(arg_no_quotes);
		}
		i++;
	}
	ft_expander(shell);
	//shell->command_args = ft_splitting(shell->command, ' ');
	//command = quote_remover(shell->command_args[0]);
	//free(shell->command_splitted[0]);
	//shell->command_args[0] = ft_strdup(command);
	//free(command);
	//handle_redirects(shell);
	if(execute_single_cmd(shell, shell->command_args[0]))
	{
		free_splited(shell->command_args);
		return (1);
	}
	get_exit_status(shell);
	free_splited(shell->command_args);
	return (0);
}

char	**remove_redirs(char *command)
{
	int		i;
	char	**command_args;

	command_args = ft_splitting(command, ' ');
	i = 0;
	while(command_args[i])
	{
		if(check_closed_quotes(command_args[i]) == 1)
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
			command_args[i] = 0;
			break ;
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