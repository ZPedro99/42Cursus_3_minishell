/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/17 11:10:34 by jomirand         ###   ########.fr       */
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
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while(env[i] != '=')
		i++;
	temp = ft_strjoin("declare -x ", env);
	exp = malloc(sizeof(char) * (ft_strlen(temp) + 5));
	i = 0;
	j = 0;
	while(temp[i])
	{
		exp[j] = temp[i];
		if (temp[i] == '=')
		{
			j++;
			exp[j] = '"';
		}
		i++;
		j++;
	}
	exp[j] = '"';
	j++;
	exp[j] = '\0';
	free(temp);
	return(exp);
}