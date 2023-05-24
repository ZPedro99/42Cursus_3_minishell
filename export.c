/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/23 14:58:12 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_exp_vars(char **env)
{
	t_list	*temp;
	t_list	*head;
	int		i;

	i = 1;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(create_exp_node(env[0])));
	temp = head;
	while (env[i])
	{
		temp->next = ft_lstnew(create_exp_node(env[i]));
		temp = temp->next;
		i++;
	}
	return (head);
}

t_env	*create_exp_node(char *env)
{
	t_env	*exp_var;

	exp_var = malloc(sizeof(t_env));
	exp_var->name = get_var_name(env);
	exp_var->info = get_exp_info(env);
	return (exp_var);
}

char	*get_exp_info(char *env)
{
	char	*value;
	char	*name;
	char	*temp1;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (env[i] != '=')
	{
		i++;
		x++;
	}
	value = malloc(sizeof(char) * ((ft_strlen(env + i)) + 3));
	name = malloc(sizeof(char) * ((ft_strlen(env) - ft_strlen(env + i)) + 2));
	name = get_name(name, env);
	value = get_value(value, env, x);
	temp1 = ft_strjoin("declare -x ", name);
	free(name);
	name = ft_strjoin(temp1, value);
	free(temp1);
	free(value);
	return (name);
}

char	*get_name(char *name, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=')
	{
		name[j] = env[i];
		i++;
		j++;
	}
	name[j] = '=';
	j++;
	name[j] = '\0';
	return (name);
}

char	*get_value(char *value, char *env, int x)
{
	int	i;

	i = 1;
	value[0] = '"';
	x++;
	while (env[x] != '\0')
	{
		value[i] = env[x];
		i++;
		x++;
	}
	value[i] = '"';
	i++;
	value[i] = '\0';
	return (value);
}
