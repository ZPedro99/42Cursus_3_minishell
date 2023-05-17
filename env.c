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
	t_list	*temp;
	t_list	*head;
	int		i;

	i = 1;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(create_env_node(env[0])));
	temp = head;
	while (env[i])
	{
		temp->next = ft_lstnew(create_env_node(env[i]));
		temp = temp->next;
		i++;
	}
	return(head);
}

t_env	*create_env_node(char *env)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	env_var->name = get_var_name(env);
	env_var->info = ft_strdup(env);
	return(env_var);
}

char	*get_var_name(char *env)
{
	int		i;
	char	*env_name;

	i = 0;
	while(env[i] != '=')
		i++;
	env_name = malloc(sizeof(char) * i + 1);
	ft_strlcpy(env_name, env, i + 1);
	return(env_name);
}

void	get_prompt(t_minishell *shell)
{
	char	*username;
	char	*seat;
	char	*temp;
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
	seat = malloc(sizeof(char) * j + 4);
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
	seat[j] = ' ';
	j++;
	seat[j] = '\0';
	shell->prompt = ft_strjoin(username, seat);
	free(seat);
}
