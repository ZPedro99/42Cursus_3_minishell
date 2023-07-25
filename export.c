/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:45:06 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 10:24:16 by jomirand         ###   ########.fr       */
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
	if (ft_search(env, '=') == 0)
	{
		exp_var->info = ft_strdup(" ");
		return (exp_var);
	}
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
	int	value;

	value = ft_search(str, '=');
	if (value == 0)
	{
		if (ft_check_dup(shell, str) == 0)
			return ;
		else
			ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
		return ;
	}
	if (ft_check_dup(shell, str) == 1)
	{
		if (value == 1)
		{
			if (ft_check_exp(shell, str) == 0)
			{
				ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
				ft_lstadd_back(&shell->env, ft_lstnew(create_env_node(str)));
				change_struct(shell, str);
			}
			return ;
		}
	}
}
