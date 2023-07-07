/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:34 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/07 15:07:33 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if(strchr(str, ':'))
		ft_putstr_fd("Minishell: unset : not a valid identifier", 2);
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
			if(string_comp(((t_env *)(head->content))->info, " "))
				free(((t_env *)(head->content))->info);
			free(((t_env *)(head->content)));
			free(head);
			free(temp2);
			return(0);
		}
	}
	free(temp2);
	return(0);
}
