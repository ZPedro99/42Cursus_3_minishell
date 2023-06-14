/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:53 by jomirand          #+#    #+#             */
/*   Updated: 2023/06/14 18:05:30 by jomirand         ###   ########.fr       */
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

extern int	g_exit_status;

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
int			main(int argc, char **argv, char **envp);
void		obtain_vars(t_minishell *shell);
void		read_command(t_minishell *shell);
char		**save_paths(char *paths);
int			number_of_paths(char *paths);

//***********env***********//
t_list	*get_env_vars(char **env);
t_env		*create_env_node(char *env);
char		*get_var_name(char *env);
char		*get_var_value(char *env);

//***********export***********//
t_list	*get_exp_vars(char **env);
t_env		*create_exp_node(char *env);
char		*get_exp_info(char *env);
char		*get_exp_name(char *env);
void		place_exp_var(t_minishell *shell, char *str);

//***********export2***********//
int			ft_check_dup(t_minishell *shell, char *str);
void		change_value_exp(t_minishell *shell, char *str, char *exp_name);
void		change_value_env(t_minishell *shell, char *str, char *name);
int			ft_check_dup2(t_minishell *shell, char *str);
int			ft_check_exp(t_minishell *shell, char *str);

//***********free***********//
void		free_env(t_list *lst);
void		free_export(t_list *lst);
void		free_export1(t_list *lst);
void		free_struct(t_minishell *shell);
void		free_splited(t_minishell *shell);
void		free_copies(char **copy);

//***********parsing***********//
int			parsing(t_minishell *shell);
void		print_env(t_minishell *shell);
char		**env_copy(t_list *lst);
void		print_exp(t_minishell *shell);
char		**sort_exp(t_list *lst, t_list *head);
void		check_args(char **command, t_minishell *shell);
int			check_exp_input(char *str);
void		other_commands(t_minishell *shell);
char		*remove_quotes(char *command);

//***********pwd***********//
void		print_pwd(t_minishell *shell);

//***********echo***********//
void		print_echo(t_minishell *shell);
int			print_echo2(t_minishell *shell, int	word_num, int ret);
int			print_normal_words(char *str);
int			check_pairs(char *str, int quote_count, char quote_type);
int			print_trimmed_string(char *str, int quote_count, char quote_type, int flag);
char		*quote_remover(char *str);
void	handle_quotes(char *str);

//***********echo_utils***********//
int			wordcount(char *s, char c);
int			check_flag(char *flag);
int			counting_quote(char *str, char c);
int			check_dollar_sign(char *str, t_minishell *shell);
char		*get_dup_str(char *str);

//***********echo_utils2***********//
int			ft_echo_es(t_minishell *shell, int i);

//***********cd***********//
void		print_cd(t_minishell *shell);
void		change_env_and_exp(t_list *env, t_list *exp, char *old_pwd, char *new_pwd);
void		change_exp(t_list *exp, char *old_pwd, char *new_pwd);
char		*change_dir(t_list *env, char *str);
//***********cd2***********//
void		change_dir_home(t_minishell *shell);
void		change_dir_minus(t_minishell *shell);
void		change_dir_dotdot(t_minishell *shell);
void		change_dir_rest(t_minishell *shell);
//***********utils***********//

int			string_comp(char *s1, char *s2);
int			len_compare(char *s1, char *s2);
char		*join_quotes(char *str);
void		get_prompt(t_minishell *shell);
char		*get_prompt2(int i, int j, char *temp);

//***********utils2***********//
int			ft_search(char *str, char c);

//***********unset***********//

void		do_unset(t_minishell *shell);
char		*adjust_name_env(char *str);
void		unset_env(t_minishell *shell, t_list *temp, int i);
void		unset_exp(t_minishell *shell, t_list *temp, int i);

//***********signals***********//

void		handle_signals(void);
void		sighand(int signal);

//***********exit***********//

void	get_exit_status(int status);

#endif