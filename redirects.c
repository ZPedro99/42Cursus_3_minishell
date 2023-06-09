/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:23:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/12 11:27:42 by emsoares         ###   ########.fr       */
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
			redirect_output(i, command_args);
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
			here_doc(command_args[i + 1]);
			shell->stdin_fd = open(".heredoc", O_RDONLY);
			//if(shell->stdin_fd < 0)
				//handle_error
			unlink(".heredoc");
		}
		i++;
	}
	//free_splited(command_args);
	return(command_args);
}

void	redirect_output(int i, char **args)
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
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	redirect_input(int i, char **args)
{
	int	file_fd;

	file_fd = open(args[i + 1], O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}

void	redirect_append(int i, char **args)
{
	int	file_fd;

	file_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	here_doc(char *delimiter)
{
	int		temp_file;
	char	*input;

	temp_file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	//if(temp_file < 0)
		//handle_error
	while(1)
	{
		input = readline("> ");
		//if(!input)
			//handle_error
		if(string_comp(input, delimiter))
			break ;
		//if(ft_strrchr(input, '$'))
			//input = expander
		ft_putstr_fd(input, temp_file);
		ft_putchar_fd('\n', temp_file);
		free(input);
	}
	free(input);
	close(temp_file);
}
