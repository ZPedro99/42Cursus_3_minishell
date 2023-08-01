/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:58 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/14 17:41:22 by emsoares         ###   ########.fr       */
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
	return (head);
}

t_env	*create_env_node(char *env)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	env_var->name = get_var_name(env);
	env_var->info = get_var_value(env);
	return (env_var);
}

char	*get_var_name(char *env)
{
	int		i;
	char	*env_name;

	i = 0;
	if (ft_search(env, '=') == 0)
	{
		env_name = ft_strdup(env);
		return (env_name);
	}
	while (env[i] != '=' && env[i] != '\0')
		i++;
	env_name = malloc(sizeof(char) * i + 2);
	ft_strlcpy(env_name, env, i + 1);
	env_name[i] = '=';
	i++;
	env_name[i] = '\0';
	return (env_name);
}

char	*get_var_value(char *env)
{
	int		i;
	int		j;
	char	*env_value;
	int		size;

	size = ft_strlen(env);
	i = 0;
	j = 0;
	if (ft_search(env, '=') == 0)
	{
		env_value = ft_strdup("");
		return (env_value);
	}
	while (env[i] != '=')
		i++;
	env_value = malloc(sizeof(char) * (size - i + 1));
	i++;
	while (env[i] != '\0')
	{
		env_value[j] = env[i];
		j++;
		i++;
	}
	env_value[j] = '\0';
	return (env_value);
}

char	**env_copy(t_list *lst)
{
	char	**env_cpy;
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	env_cpy = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (temp)
	{
		env_cpy[i] = ft_strjoin(((t_env *)(temp->content))->name,
				((t_env *)(temp->content))->info);
		temp = temp->next;
		i++;
	}
	env_cpy[i] = 0;
	return (env_cpy);
}
