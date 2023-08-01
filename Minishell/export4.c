/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:15:13 by emsoares          #+#    #+#             */
/*   Updated: 2023/07/25 10:27:24 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_exp2(t_minishell *shell, char *temp2)
{
	t_list	*previous;
	t_list	*head;

	head = shell->exp;
	while (head)
	{
		if (!string_comp(((t_env *)(head->content))->name, temp2))
		{
			previous = head;
			head = head->next;
		}
		else
		{
			previous->next = head->next;
			free(((t_env *)(head->content))->name);
			if (string_comp(((t_env *)(head->content))->info, " "))
				free(((t_env *)(head->content))->info);
			free(((t_env *)(head->content)));
			free(head);
			free(temp2);
			return (0);
		}
	}
	free(temp2);
	return (0);
}

void	print_exp(t_minishell *shell)
{
	t_list	*temp;
	char	**exp_array;
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
				break ;
			temp = temp->next;
		}
		printf("%s%s\n", ((t_env *)(temp->content))->name,
			((t_env *)(temp->content))->info);
		temp = shell->exp;
		i++;
	}
	free_splited(exp_array);
}

char	**sort_exp(t_list *lst, t_list *head)
{
	int		size;
	char	**exp_array;
	int		i;

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
	exp_array = sort_exp2(exp_array, i, size);
	return (exp_array);
}

char	**sort_exp2(char **exp_array, int i, int size)
{
	char	*temp1;
	char	*temp2;
	int		size_string;

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
	int	i;

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
