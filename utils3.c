/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:41:59 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 16:22:40 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_available_paths(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		if (string_comp(((t_env *)(temp->content))->name, "PATH="))
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_equal(char *str, int i)
{
	char	temp;
	int		count;

	count = 0;
	temp = str[i];
	if (temp == '\'')
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (0);
			if (str[i] == '\'')
				count++;
			i++;
		}
		if (count % 2 == 0)
			return (1);
		else
			return (-1);
	}
	else if (temp == '"')
		return (check_equal2(str, i, count));
	return (0);
}

int	check_equal2(char *str, int i, int count)
{
	while (str[i])
	{
		if (str[i] == '\'')
			return (0);
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	else
		return (-1);
	return (0);
}

int	check_args(char **command, t_minishell *shell)
{
	int		i;
	int		x;
	int		status;
	char	*str;

	i = 1;
	x = 0;
	str = 0;
	wait(&status);
	while (command[i] != NULL)
		i++;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status != 2)
	{
		if (i >= 2)
			if (check_args2(&x, command, str, shell) == 1)
				return (1);
	}
	if (x == 0)
		return (0);
	return (1);
}

int	check_args2(int *x, char **cmd, char *str, t_minishell *shell)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_exp_quotes(cmd[i]) == 0 || check_exp_quotes(cmd[i]) == -1)
		{
			printf("Error in export variable, check quotes!\n");
			return (1);
		}
		if (check_exp_quotes(cmd[i]) == 1)
		{
			str = quote_remover_exp(cmd[i]);
			if (check_exp_input(str) == 0)
			{
				(*x) = 1;
				printf("minishell: export: `%s': not a valid identifier\n", str);
			}
			else
				place_exp_var(shell, str);
			free(str);
		}
		i++;
	}
	return (0);
}
