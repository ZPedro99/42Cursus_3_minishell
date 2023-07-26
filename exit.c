/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:17:30 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 11:48:00 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_minishell *shell)
{
	int		i;
	pid_t	j;
	int		status;

	i = 0;
	status = 0;
	while (i < shell->pipes + 1)
	{
		signal(SIGINT, &sigint_on_child);
		j = waitpid(shell->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		i++;
	}
}

int	ft_exit_status(t_minishell *shell)
{
	int	count;
	int	status;

	count = ft_word_count(shell->command_args);
	wait(&status);
	if (WIFEXITED(status))
		return (exit_status2(shell, count));
	return (0);
}

int	exit_status2(t_minishell *shell, int count)
{
	if (count == 1)
	{
		printf("exit\n");
		g_exit_status = 0;
		return (0);
	}
	if (check_arg(shell->command_args[1]) == 0)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		g_exit_status = 2;
		return (0);
	}
	if (count > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	else
		return (exit_status3(shell));
}

int	exit_status3(t_minishell *shell)
{
	long long	num;
	char		*str;

	num = ft_atol(shell->command_args[1]);
	str = ft_ltoa(num);
	if (ft_strncmp(str, shell->command_args[1], ft_strlen(str)) != 0)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		g_exit_status = 2;
		free(str);
		return (0);
	}
	free(str);
	printf("exit\n");
	num = ft_atol(shell->command_args[1]);
	g_exit_status = (num % 256);
	return (0);
}
