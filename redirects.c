/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:23:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/14 14:21:16 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_redirects(t_minishell *shell, char *command)
{
	int	i;
	int	num_words;
	char	**command_args;

	i = 0;
	num_words = countwords(command);
	command_args = ft_splitting(command, ' ');
	while(command_args[i])
	{
		if(string_comp(command_args[i], ">"))
		{
			if(redirect_output(i, command_args))
			{
				free_splited(command_args);
				free_struct(shell);
				free(command);
				exit(2);
			}
			if(i == num_words - 2)
			{
				free(command_args[i]);
				free(command_args[i + 1]);
				free(command_args[i + 2]);
				command_args[i] = 0;
				return(command_args);
			}
		}
		if(string_comp(command_args[i], "<"))
		{
			redirect_input(i, command_args);
			if(i == num_words - 2)
			{
				free(command_args[i]);
				free(command_args[i + 1]);
				command_args[i] = 0;
				return(command_args);
			}
		}
		if(string_comp(command_args[i], ">>"))
		{
			redirect_append(i, command_args);
			if(i == num_words - 2)
			{
				free(command_args[i]);
				free(command_args[i + 1]);
				command_args[i] = 0;
				return(command_args);
			}
		}
		if(string_comp(command_args[i], "<<"))
		{
			if(here_doc(command_args[i + 1]))
			{
				free_splited(command_args);
				free_struct(shell);
				free(command);
				exit(2);
			}
			if(i == num_words - 2 && i == 0)
			{
				free(command_args[i]);
				free(command_args[i + 1]);
				command_args[i] = 0;
				return(command_args);
			}
			shell->stdin_fd = open(".heredoc", O_RDONLY);
			if (shell->stdin_fd < 0)
			{
				ft_putstr_fd("Minishell: no file specified in redirect '<<'.\n", 2);
				free_splited(command_args);
				free_struct(shell);
				free(command);
				exit(2);
			}
			unlink(".heredoc");
		}
		i++;
	}
	//free_splited(command_args);
	return(command_args);
}

int	redirect_output(int i, char **args)
{
	int		file_fd;
	char	*temp;

	if(check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return(1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return(0);
}

int	redirect_input(int i, char **args)
{
	int	file_fd;
	char	*temp;

	if(check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_RDONLY);
	if(!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<'.\n", 2);
		return(1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return(0);
}

int	redirect_append(int i, char **args)
{
	int	file_fd;
	char	*temp;

	if(check_closed_quotes(args[i + 1]) == 1)
	{
		temp = quote_remover(args[i + 1]);
		free(args[i + 1]);
		args[i + 1] = ft_strdup(temp);
	}
	file_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if(!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
		return(1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return(0);
}

int	here_doc(char *delimiter)
{
	int		temp_file;
	char	*input;

	temp_file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if(temp_file < 0)
	{
		ft_putstr_fd("Minishell: could not open .heredoc file\n", 2);
		return(1);
	}
	while(1)
	{
		input = readline("> ");
		if(!input)
		{
			ft_putstr_fd("Minishell: heredoc interrupted by end-of-file\n", 2);
			return(1);
		}
		if(string_comp(input, delimiter))
			break ;
		ft_putstr_fd(input, temp_file);
		ft_putchar_fd('\n', temp_file);
		free(input);
	}
	free(input);
	close(temp_file);
	return(0);
}
