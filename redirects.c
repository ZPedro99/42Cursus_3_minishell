/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:23:20 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/07 12:26:45 by jomirand         ###   ########.fr       */
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
			redirect_output(shell, i);
		if(string_comp(command_args[i], "<"))
			redirect_input(shell, i);
		if(string_comp(command_args[i], ">>"))
		{
			redirect_append(shell, i);
			if(i == 1)
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

void	redirect_output(t_minishell *shell, int i)
{
	int	file_fd;

	file_fd = open(shell->command_args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	redirect_input(t_minishell *shell, int i)
{
	int	file_fd;

	file_fd = open(shell->command_args[i + 1], O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}

void	redirect_append(t_minishell *shell, int i)
{
	int	file_fd;

	file_fd = open(shell->command_args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
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