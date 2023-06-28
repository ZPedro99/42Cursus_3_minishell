/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:17:30 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/28 09:49:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_exit_status = 128 + WEXITSTATUS(status);
	//printf("status is: %d\n", g_exit_status);
	//exit(g_exit_status);
}

void	get_exit_status_multi(t_minishell *shell)
{
	int		i;
	pid_t	j;
	int		status;

	i = 0;
	status = 0;
	while(i < shell->pipes + 1)
	{
		j = waitpid(shell->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WEXITSTATUS(status);
		i++;
	}
	//printf("status is: %d\n", g_exit_status);
	//exit(g_exit_status);
}

int	ft_exit_status(t_minishell *shell)
{
	int count;
	long long	num;
	char	*str;

	str = 0;
	num = 0;
	count = ft_word_count(shell->command_splited);
	if (count == 1)
	{
		printf("exit\n");
		g_exit_status = 0;
		return (g_exit_status);
	}
	if (count > 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (check_arg(shell->command_splited[1]) == 0)//se tiver letras
	{
		printf("exit\n");
		printf("minishell: %s: numeric argument required\n", shell->command_splited[1]);
		g_exit_status = 2;
		return (g_exit_status);
	}
	else
	{
		num = ft_atol(shell->command_splited[1]);
		str = ft_ltoa(num);
		if (ft_strncmp(str, shell->command_splited[1], ft_strlen(str)) != 0)
		{
			printf("exit\n");
			printf("minishell: %s: numeric argument required\n", shell->command_splited[1]);
			g_exit_status = 2;
			free(str);
			return (g_exit_status);
		}
		free(str);
		printf("exit\n");
		num = ft_atol(shell->command_splited[1]);
		g_exit_status = (num % 256);
		return (g_exit_status);
	}
	return (0);
}

int	ft_word_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return(0);
		i++;
	}
	return (1);
}

long long	ft_atol(const char *str)
{
	int					i;
	long				sign;
	long long			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

static char	*posnum(char *str, long long n, int len)
{
	long	x;

	len--;
	x = n;
	while (len >= 0)
	{
		str[len] = x % 10 + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static char	*negnum(char *str, long long n, int len)
{
	long	x;

	x = n;
	str[0] = '-';
	len--;
	x = x * (-1);
	while (len > 0)
	{
		str[len] = (x % 10) + '0';
		x = x / 10;
		len--;
	}
	return (str);
}

static int	int_len(long long n)
{
	int		i;
	long	x;

	x = n;
	i = 0;
	if (x <= 0)
	{
		x = x *(-1);
		i++;
	}
	while (x > 0)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long long n)
{
	char	*str;
	int		len;

	len = int_len(n);
	str = (char *) malloc (sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str = negnum(str, n, len);
	}
	else if (n == 0)
		str[0] = '0';
	else
		str = posnum(str, n, len);
	return (str);
}
