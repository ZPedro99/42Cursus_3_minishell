/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:47:25 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/07 15:15:00 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return (0);
}

int	counting_pipes(t_minishell *shell)
{
	int		i;
	char	ignore;
	int		flag;

	i = 0;
	ignore = 0;
	flag = 0;
	while(shell->command[i])
	{
		if((shell->command[i] == '"' || shell->command[i] == '\'') && !flag)
		{
			ignore = '"';
			flag = 1;
			i++;
		}
		if((shell->command[i] == '"' || shell->command[i] == '\'') && flag)
		{
			ignore = 0;
			flag = 0;
			i++;
			if(shell->command[i] == '\0')
				break ;
		}
		if(shell->command[i] == '|' && !ignore)
			shell->pipes++;
		if(shell->command[i] == '\0')
			break ;
		i++;
	}
	return(shell->pipes);
}

int	check_available_paths(t_list *env)
{
	t_list	*temp;

	temp = env;
	while(temp)
	{
		if(string_comp(((t_env *)(temp->content))->name, "PATH="))
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_equal(char *str, int i)
{
	char temp;
	int count;

	count = 0;
	temp = str[i];
	if(temp == '\'')
	{
			while(str[i])
			{
				if (str[i] == '"')
					return(0);
				if (str[i] == '\'')
					count++;
				i++;
			}
			if(count % 2 == 0)
				return (1);
			else
				return (-1);
	}
	else if(temp == '"')
	{
		while(str[i])
		{
			if (str[i] == '\'')
				return(0);
			if (str[i] == '"')
				count++;
			i++;
		}
		if(count % 2 == 0)
			return (1);
		else
			return (-1);
	}
	return(0);
}

int	check_args(char **command, t_minishell *shell)
{
	int	i;
	int	x;
	int	status;
	char	*str;

	i = 1;
	x = 0;
	wait(&status);

	while (command[i] != NULL)
		i++;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if(g_exit_status != 2)
	{
		if(i >= 2)
		{
			i = 1;
			while(command[i])
			{
				if(check_exp_quotes(command[i]) == 0)
				{
					printf("Error in export variable, check quotes!\n");//se tiver quotes diferentes
					return(1);
				}
				if(check_exp_quotes(command[i]) == -1)
				{
					printf("Error in export variable, quote must have their pair!\n");
					return (1);
				}
				if(check_exp_quotes(command[i]) == 1)
				{
					str = quote_remover_exp(command[i]);
					if(check_exp_input(str) == 0)
					{
						x = 1;
						//free(str);
						printf("minishell: export: `%s': not a valid identifier\n", str);
					}
					else
						place_exp_var(shell, str);
					free(str);
				}
				i++;
			}
		}
	}
	if (x == 0)
		return (0);
	return (1);
}

void	check_export_args(t_minishell *shell)
{
	int	i;

	i = 0;
	while(shell->command_args[i])
		i++;
	if(i == 1)
		print_exp(shell);
	else if(i > 1)
	{
		//error handling
		return ;
	}
}