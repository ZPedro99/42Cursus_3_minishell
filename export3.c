/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:02:21 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/20 11:05:42 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exp(t_minishell *shell)
{
	t_list	*temp;
	char	**exp_array;
	//char	*exp_line;
	int		i;
	int		size;

	i = 0;
	size = 0;
	temp = shell->exp;
	exp_array = sort_exp(temp, shell->exp);
	while (exp_array[size])
		size++;
	while (size != i)
	{
		while (temp)
		{
			if (string_comp(exp_array[i], ((t_env *)(temp->content))->name))
			{
				//exp_line = ft_strjoin(exp_array[i], ((t_env *)(temp->content))->info);
				break ;
			}
			temp = temp->next;
		}
		printf("%s%s\n", ((t_env *)(temp->content))->name, ((t_env *)(temp->content))->info);
		//free(exp_line);
		temp = shell->exp;
		i++;
	}
	i = 0;
	while (exp_array[i])
	{
		free(exp_array[i]);
		i++;
	}
	free(exp_array);
}

char	**sort_exp(t_list *lst, t_list *head)
{
	int		size;
	int		size_string;
	char	**exp_array;
	int		i;
	char	*temp1;
	char	*temp2;

	(void)head;
	i = 0;
	size = ft_lstsize(lst);
	exp_array = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		exp_array[i] = ft_strdup(((t_env *)(lst->content))->name);
		i++;
		lst = lst->next;
	}
	exp_array[i] = 0;
	i = 0;
	while (i < size - 1)
	{
		size_string = len_compare(exp_array[i], exp_array[i + 1]);
		if (ft_strncmp(exp_array[i], exp_array[i + 1], size_string) > 0)
		{
			temp1 = ft_strdup(exp_array[i]);
			temp2 = ft_strdup(exp_array[i + 1]);
			free(exp_array[i]);
			free(exp_array[i + 1]);
			exp_array[i] = ft_strdup(temp2);
			exp_array[i + 1] = ft_strdup(temp1);
			free(temp1);
			free(temp2);
			i = 0;
		}
		else
			i++;
	}
	return (exp_array);
}

int	check_exp_quotes(char *original)
{
	int i;

	i = 0;
	while (original[i])
	{
		if (original[i] == '"' || original[i] == '\'')
		{
			if (check_equal(original, i) == 0)
				return (0);
			if (check_equal(original, i) == -1)
				return (-1);
			if (check_equal(original, i) == 1)
				return (1);
		}
		i++;
	}
	return (1);
}

int	check_exp_input(char *str)
{
	int		i;
	char	*temp;
	char	*temp1;
	temp = get_var_name(str);
	if (ft_search(temp, '=') == 1)
	{
		temp1 = ft_strdup(temp);
		free(temp);
		temp = ft_strtrim(temp1, "=");
		free(temp1);
	}
	if ((ft_isalpha(temp[0]) == 0) && temp[0] != '_')
	{
		free(temp);
		return (0);
	}
	i = 0;
	while (temp[i])
	{
		if ((ft_isalnum(temp[i]) == 1) || temp[i] == '_' )
			i++;
		else
		{
			free(temp);
			return (0);
		}
	}
	free(temp);
	return (1);
}

char *quote_remover_exp(char *str)
{
	int	i;
	char *new;
	char temp;
	int j;

	j = 0;
	i = 0;
	while(str[i] != '\'' && str[i] != '"' &&  str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		new = ft_strdup(str);
		return (new);
	}
	temp = str[i];
	new = malloc(sizeof(char) * (ft_strlen(str) - counting_quote(str, temp) + 1));
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == temp)
			i++;
		else
		{
			new[j] = str[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}