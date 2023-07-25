/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:37:27 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/25 16:15:02 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*adjust_name_env(char *str)
{
	char	*str_adjusted;

	str_adjusted = ft_strjoin(str, "=");
	return (str_adjusted);
}

char	*adjust_name_exp(char *str)
{
	char	*str_adjusted_temp;
	char	*final_str;

	str_adjusted_temp = ft_strjoin("declare -x ", str);
	final_str = ft_strjoin(str_adjusted_temp, "=");
	free(str_adjusted_temp);
	return (final_str);
}
