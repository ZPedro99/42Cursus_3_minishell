/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:53 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/16 09:37:53 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	t_list	*env;
	t_list	*export;
	char	*prompt;
}				t_minishell;

//***********env***********//

t_list	*get_env_vars(char **env);
char	*print_prompt(char **env, t_minishell *shell);

#endif