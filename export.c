/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/07 14:22:22 by emsoares         ###   ########.fr       */
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
	if(ft_search(env, '=') == 0)
	{
		exp_var->info = NULL;
		return(exp_var);	
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
	int value;
	
	value = ft_search(str, '=');
	if (value == 0)
	{
		if (ft_check_dup2(shell, str) == 0)//vai procurar se existe algum node c o nome igual se houver ignora senao coloca apenas no export
			return ;
		else
			ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
		return ;
	}
	if(ft_check_dup(shell, str) == 1)
	{
		if (value == 1) //colocar export + env
		{
			if(ft_check_exp(shell, str) == 0)
			{
				ft_lstadd_back(&shell->exp, ft_lstnew(create_exp_node(str)));
				ft_lstadd_back(&shell->env, ft_lstnew(create_env_node(str)));
			}
			return ;
		}	
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

int	ft_check_dup(t_minishell *shell, char *str)
{
	t_list *head;
	char	*temp;
	char	*name;
	int	i;
	int	j;
	head = shell->exp;
	
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = '=';
	j++;
	temp[j] = '\0';
	name = ft_strjoin("declare -x ", temp);
	free(temp);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, name))
		{
			change_value_exp(shell, str, name);
			change_value_env(shell, str, name);
			return (0);
		}
		head = head->next;
	}
	free(name);
	return (1);
}

void	change_value_exp(t_minishell *shell, char *str, char *exp_name)
{
	char	*exp_value;
	char	*temp;
	t_list *temp_exp;
	
	int	i = 0;
	int	j = 0;
	int size;

	size = ft_strlen(str);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if(str[i] == '\0')
		temp = NULL;
	else
	{
		temp = malloc(sizeof(char) * (size - i + 1));
		i++;
		while(str[i] != '\0')
		{
			temp[j] = str[i];
			i++;
			j++;
		}
		temp[j] = '\0';
	}
	exp_value = ft_strjoin("\"", temp);
	free(temp);
	temp = ft_strjoin(exp_value, "\"");
	temp_exp = shell->exp;
	while (!string_comp(((t_env *)(temp_exp->content))->name, exp_name))
		temp_exp = temp_exp->next;
	free(((t_env *)(temp_exp->content))->info);
	((t_env *)(temp_exp->content))->info = ft_strdup(temp);
	free(temp);
	free(exp_name);
	free(exp_value);
}

void	change_value_env(t_minishell *shell, char *str, char *name)
{
	char	*temp;
	t_list *temp_env;
	
	int	i = 0;
	int	j = 0;
	int size;

	size = ft_strlen(str);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if(str[i] == '\0')
	{
		name = get_var_name(str);
		temp = NULL;
	}
	else
	{
		name = get_var_name(str);
		temp = malloc(sizeof(char) * (size - i + 1));
		i++;
		while(str[i] != '\0')
		{
			temp[j] = str[i];
			i++;
			j++;
		}
		temp[j] = '\0';
	}
	temp_env = shell->env;
	while (!string_comp(((t_env *)(temp_env->content))->name, name))
		temp_env = temp_env->next;
	free(((t_env *)(temp_env->content))->info);
	((t_env *)(temp_env->content))->info = ft_strdup(temp);
	free(temp);
	free(name);
}

int	ft_check_dup2(t_minishell *shell, char *str)
{
	t_list	*head;
	char 		*temp;
	char		*search;
	head = shell->exp;
	temp = ft_strjoin(str, "=");
	search = ft_strjoin("declare -x ", temp);
	free(temp);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, search))
		{
			free(search);
			return (0);
		}
		head = head->next;
	}
	free(search);
	head = shell->exp;
	search = ft_strjoin("declare -x ", str);
	while (head)
	{
		if (string_comp(((t_env *)(head->content))->name, search))
		{
			free(search);
			return (0);
		}
		head = head->next;
	}
	free(search);
	return(1);
}

int	ft_check_exp(t_minishell *shell, char *str)
{
	t_list	*previous;
	t_list	*head;
	char *temp;
	char *temp2;
	int	i = 0;

	while(str[i]!= '=')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while(str[i]!='=')
	{
		temp[i]=str[i];
		i++;
	}
	temp[i] = '\0';
	temp2 = ft_strjoin("declare -x ", temp);
	free(temp);
	head = shell->exp;
	while(head)
	{
		if(!string_comp(((t_env *)(head->content))->name, temp2))
		{
			previous = head;
			head = head->next;
		}
		else
		{
		previous->next = head->next;
		free(((t_env *)(head->content))->name);
		free(((t_env *)(head->content))->info);
		free(((t_env *)(head->content)));
		free(temp2);
		return(0);
		}	
	}
	free(temp2);
	return(0);
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
