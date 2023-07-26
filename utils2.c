/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:47:25 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/26 09:48:40 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	counting_pipes(t_minishell *shell)
{
	int		i;
	char	ignore;
	int		flag;
	char	**verify_cmds;
	int		num_words;

	i = -1;
	ignore = 0;
	flag = 0;
	num_words = ft_wordcount_meta(shell->command, ' ');
	verify_cmds = ft_splitting(shell->command, ' ');
	while (++i < num_words)
	{
		if (check_pipe(i, verify_cmds, num_words) == -1)
			return (-1);
	}
	free_splited(verify_cmds);
	i = 0;
	shell_pipes_count(shell, i, flag, ignore);
	return (shell->pipes);
}

int	check_pipe1(char **verify_cmds, int i)
{
	if (string_comp(verify_cmds[i], "|") && !verify_cmds[i + 1])
	{
		ft_putstr_fd("Minishell: no command after or before a pipe.\n", 2);
		free_splited(verify_cmds);
		return (-1);
	}
	if (ft_strrchr("<>", verify_cmds[i][0]) && !verify_cmds[i + 1])
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(verify_cmds);
		return (-1);
	}
	if (string_comp(verify_cmds[i], ">>") && !verify_cmds[i + 1])
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(verify_cmds);
		return (-1);
	}
	if (string_comp(verify_cmds[i], "<<") && !verify_cmds[i + 1])
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(verify_cmds);
		return (-1);
	}
	return (0);
}

int	check_pipe2(char **ver_cmd, int i)
{
	if (string_comp(ver_cmd[i], "|") && (!ver_cmd[i - 1] || !ver_cmd[i + 1]))
	{
		ft_putstr_fd("Minishell: no command after or before a pipe.\n", 2);
		free_splited(ver_cmd);
		return (-1);
	}
	if (ft_strrchr("<>", ver_cmd[i][0]) && (!ver_cmd[i - 1] || !ver_cmd[i + 1]))
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(ver_cmd);
		return (-1);
	}
	if (string_comp(ver_cmd[i], ">>") && (!ver_cmd[i - 1] || !ver_cmd[i + 1]))
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(ver_cmd);
		return (-1);
	}
	if (string_comp(ver_cmd[i], "<<") && !ver_cmd[i + 1])
	{
		ft_putstr_fd("Minishell: no command after or before a redirect.\n", 2);
		free_splited(ver_cmd);
		return (-1);
	}
	return (0);
}

void	shell_pipes_count(t_minishell *shell, int i, int flag, char ignore)
{
	shell->pipes = 0;
	while (shell->command[i])
	{
		if ((shell->command[i] == '"' || shell->command[i] == '\'') && !flag)
		{
			ignore = '"';
			flag = 1;
			i++;
		}
		if ((shell->command[i] == '"' || shell->command[i] == '\'') && flag)
		{
			ignore = 0;
			flag = 0;
			i++;
			if (shell->command[i] == '\0')
				break ;
		}
		if (shell->command[i] == '|' && !ignore)
			shell->pipes++;
		if (shell->command[i] == '\0')
			break ;
		i++;
	}
}
