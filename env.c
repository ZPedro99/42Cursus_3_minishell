/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:58 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/16 10:57:58 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env_vars(char **env)
{
	t_list	*head;
	t_list	*temp;
	int		i;

	head = NULL;
	i = 1;
	ft_lstadd_front(&head, ft_lstnew(env[0]));
	temp = head;
	while (env[i])
	{
		temp->next = ft_lstnew(env[i]);
		temp = temp->next;
		i++;
	}
	return(head);
}

char	*print_prompt(char **env, t_minishell *shell)
{
	char	*username;
	char	*seat;
	char	*temp;
	int		size;
	int		i;
	int		j;

	username = getenv("USER");
	temp = getenv("SESSION_MANAGER");
	i = 0;
	while(temp[i] != '/')
		i++;
	i++;
	j = i;
	while(temp[j] != '.')
		j++;
	seat = malloc(sizeof(char) * j + 3);
	j = 1;
	seat[0] = '@';
	while(temp[i] != '.')
	{
		seat[j] = temp[i];
		i++;
		j++;
	}
	seat[j] = '>';
	j++;
	seat[j] = '\0';
	shell->prompt = ft_strjoin(username, seat);
	return(shell->prompt);
}
