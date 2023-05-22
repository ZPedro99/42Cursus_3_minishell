/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/19 13:10:21 by emsoares         ###   ########.fr       */
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
	return(head);
}

t_env	*create_exp_node(char *env)
{
	t_env	*exp_var;

	exp_var = malloc(sizeof(t_env));
	exp_var->name = get_var_name(env);
	exp_var->info = get_exp_info(env);
	return(exp_var);
}

char	*get_exp_info(char *env)
{
	char	*exp;
	char	*value;
	char  *name;
	char 	*temp1;
	int		i;
	int		j;
	int		size;
	int size1;
	int x;
	i = 0;
	j = 0;
	x = 0;
	size = 0;
	size1 = 0;
	while(env[i] != '=')
	{
		i++;
		x++;
	}
	size = ft_strlen(env + i);
	size1= ft_strlen(env) - size;
	value = malloc(sizeof(char) * (size + 3));
	name = malloc(sizeof(char) * (size1 + 1));
	i = 0;
	while(env[i] != '=')
	{
		name[j] = env[i];
		i++;
		j++;
	}
	name[j] = '=';
	j++;
	name[j] = '\0';
	i++;
	j = 1;
	value[0] = '"';
	x++;
	while(env[x] != '\0')
	{
		value[j] = env[x];
		j++;
		x++;
	}
	value[j] = '"';
	j++;
	value[j] = '\0';
	
	temp1 = ft_strjoin("declare -x ", name);
	free(name);
	exp = ft_strjoin(temp1, value);
	free(temp1);
	free(value);
	return(exp);
}

	/* char *exp;
	char *temp;
	int size;
	int i;
	int j;

	i = 0;
	j = 0;
	size = 0;
	
	temp = ft_strjoin("declare -x ", env);
	size = ft_strlen(temp);
	exp = (char *)malloc(sizeof(char) * (size + 3));
	i = 0;
	j = 0;
	while (temp[i])
	{
		exp[j] = temp[i];
		if (temp[i] == '=')
		{
			j++;
			exp[j] = '"';
			j++;
		}
		else
			j++;
		i++;
	}
	//j++;
	exp[j] = '"';
	j++;
	exp[j] = '\0';
	free(temp);
	return(exp); */