/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:53 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/07 14:34:47 by emsoares         ###   ########.fr       */
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
# include <signal.h>

typedef struct s_minishell
{
	t_list	*env;
	t_list	*exp;
	char	**env_array;
	char	*pwd;
	char	*old_pwd;
	char	*prompt;
	char	*command;
	char	**command_splited;
	char	*home;
	char	**paths;
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;

//***********main***********//

void	read_command(t_minishell *shell);
void	obtain_vars(t_minishell *shell);

//***********env***********//

t_list	*get_env_vars(char **env);
void	get_prompt(t_minishell *shell);
t_env	*create_env_node(char *env);
char	*get_var_name(char *env);
char	*get_var_value(char *env);

//***********export***********//

t_list	*get_exp_vars(char **env);
t_env	*create_exp_node(char *env);
char	*get_exp_info(char *env);
char	*get_name(char *name, char *env);
char	*get_value(char *value, char *env, int x);
char	*get_exp_name(char *env);
void	place_exp_var(t_minishell *shell, char *str);
int		ft_search(char *str, char c);
void	change_value_exp(t_minishell *shell, char *str, char *exp_name);
int	ft_check_dup(t_minishell *shell, char *str);
int	ft_check_dup2(t_minishell *shell, char *str);
int	ft_check_exp(t_minishell *shell, char *str);
void	change_value_env(t_minishell *shell, char *str, char *name);
//***********free***********//

void	free_env(t_list *lst);
void	free_export(t_list *lst);
void	free_export1(t_list *lst);
void	free_struct(t_minishell *shell);

//***********parsing***********//

int		parsing(t_minishell *shell);
void	print_env(t_minishell *shell);
char	**env_copy(t_list *lst);
void	print_exp(t_minishell *shell);
char	**sort_exp(t_list *lst, t_list *head);
void	check_args(char **command, t_minishell *shell);
int		check_exp_input(char *str);

//***********pwd***********//
void	print_pwd(t_minishell *shell);

//***********echo***********//
void	print_echo(t_minishell *shell);
int		wordcount(char *s, char c);
int		check_flag(char *flag);
int		counting_quote(char *str, char c);
int		check_dollar_sign(t_minishell *shell);

//***********cd***********//
void	print_cd(t_minishell *shell);
void	change_env_and_exp(t_list *env, t_list *exp, char *old_pwd, char *new_pwd);
char	*change_dir(t_list *env, char *str);

//***********utils***********//

int		string_comp(char *s1, char *s2);
int		len_compare(char *s1, char *s2);
char	*join_quotes(char *str);

//***********unset***********//

void	do_unset(t_minishell *shell);
char	*adjust_name_env(char *str);
void	unset_env(t_minishell *shell, t_list *temp, int i);
void	unset_exp(t_minishell *shell, t_list *temp, int i);

//***********signals***********//

void	handle_signals(void);
void	sighand(int signal);

#endif