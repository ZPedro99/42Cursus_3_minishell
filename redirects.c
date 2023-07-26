/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:23:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 15:38:57 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_redirects(t_minishell *shell, char *command)
{
	int		i;
	int		num_words;
	char	**command_args;

	i = -1;
	num_words = countwords(command);
	command_args = ft_splitting(command, ' ');
	while (command_args[++i])
	{
		if (string_comp(command_args[i], ">"))
		{
			handle_output(shell, i, command_args, command);
			return (place_null(i, num_words, command_args), command_args);
		}
		if (string_comp(command_args[i], "<"))
		{
			handle_input(shell, i, command_args, command);
			return (place_null(i, num_words, command_args), command_args);
		}
		command_args = double_sign(shell, i, command_args, command);
		if (!command_args[i])
			return (command_args);
	}
	return (command_args);
}

int	redirect_output(int i, char **args)
{
	int		file_fd;
	char	*temp;

	if (!args[i + 1])
		return (1);
	if (check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	redirect_input(int i, char **args)
{
	int		file_fd;
	char	*temp;

	if (check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_RDONLY);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}

int	redirect_append(int i, char **args)
{
	int		file_fd;
	char	*temp;

	if (check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	here_doc(char *delimiter)
{
	int		tp_file;
	char	*input;

	tp_file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (tp_file < 0)
	{
		ft_putstr_fd("Minishell: could not open .heredoc file\n", 2);
		return (1);
	}
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (ft_putstr_fd("Minishell: heredoc interrupted\n", 2), 1);
		if (string_comp(input, delimiter))
			break ;
		ft_putstr_fd(input, tp_file);
		ft_putchar_fd('\n', tp_file);
		free(input);
	}
	free(input);
	close(tp_file);
	return (0);
}
