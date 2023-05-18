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
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	*prompt;
	char	*command;
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;


//***********env***********//

t_list	*get_env_vars(char **env);
void	get_prompt(t_minishell *shell);
t_env	*create_env_node(char *env);
char	*get_var_name(char *env);

//***********export***********//

t_list	*get_exp_vars(char **env);
t_env	*create_exp_node(char *env);
char	*get_exp_info(char *env);

//***********free***********//

void	free_lists(t_list *lst);

//***********parsing***********//

int		parsing(t_minishell *shell);
void	print_env(t_minishell *shell);
char	**env_copy(t_list *lst);
int		string_comp(char *s1, char *s2);
void	print_exp(t_minishell *shell);

#endif
