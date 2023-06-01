/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/01 14:01:43 by emsoares         ###   ########.fr       */
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
	exp_var->name = get_exp_name(env);
	exp_var->info = get_exp_info(env);
	return (exp_var);
}

char	*get_exp_info(char *env)
{
	char	*info;
	char	*initial_info;

	info = get_var_value(env);
	initial_info = ft_strjoin("\"", info);
	free(info);
	info = ft_strjoin(initial_info, "\"");
	free(initial_info);
	return (info);
}

char	*get_exp_name(char *env)
{
	char	*name;
	char	*initial_name;

	initial_name = get_var_name(env);
	name = ft_strjoin("declare -x ", initial_name);
	free(initial_name);
	return (name);
}

void	place_exp_var(t_minishell *shell, char *str)
{
	int value;

	value = ft_search(str, '=');
	if (value == 0) //so tenho de colocar no export sem o =
	{
		ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
		return ;
	}
	if (value == 1) //colocar export + env
	{
		ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
		ft_lstadd_back(&shell->env, ft_lstnew(create_env_node(str)));
		return ;
	}
}

int	ft_search(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return (0);
}

/* char	*get_name(char *name, char *env)
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
} */

/* char	*get_value(char *value, char *env, int x)
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
} */
