/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:37:53 by jomirand          #+#    #+#             */
/*   Updated: 2023/07/26 17:35:01 by jomirand         ###   ########.fr       */
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
# include <limits.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	char	**command_splitted;
	char	**command_splitted_pipe;
	char	*home;
	char	**paths;
	int		pipes;
	int		*pipes_fd;
	int		stdin_fd;
	int		stdout_fd;
	char	**command_args;
	pid_t	*pid;
	int		*expander_flags;
	int		exit_flag;
	int		expander_flag;
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
int			read_command2(t_minishell *shell);
char		**save_paths(char *paths);

//***********main2***********//
int			number_of_paths(char *paths);
int			check_command(t_minishell *shell);
int			check_command2(char **cmd_args);

//***********builtins***********//
int			builtin_check(t_minishell *sh, char **cmd_args, char *cmd);
int			builtin_check2(t_minishell *sh, char **cmd_args, char *cmd);
int			builtin_check_multi(t_minishell *sh, char *cmd);
int			builtin_check_multi2(t_minishell *sh, char *cmd);

//***********builtins2***********//
void		execute_builtins(t_minishell *shell, char *command);
void		execute_builtins_multi(t_minishell *shell, char *command);

//***********cd***********//
int			do_cd(t_minishell *shell);
int			do_cd2(t_minishell *shell);
void		change_env_exp(t_list *env, t_list *exp, char *o_pwd, char *n_pwd);
void		change_exp(t_list *exp, char *old_pwd, char *new_pwd);
char		*change_dir(t_list *env, char *str);

//***********cd2***********//
void		change_dir_home(t_minishell *shell);
void		change_dir_minus(t_minishell *shell);
void		change_dir_dotdot(t_minishell *shell);
int			change_dir_rest(t_minishell *shell);

//***********echo_utils***********//
int			wordcount(char *s, char c);
int			check_flag(char *flag);
int			counting_quote(char *str, char c);
int			check_dollar_sign(char *str, t_minishell *shell);
char		*get_dup_str(char *str);

//***********echo***********//
void		print_echo(t_minishell *shell);
int			print_echo2(t_minishell *shell);
char		quote_checker(char *str, int i, char quote);
char		*quote_remover(char *str);

//***********echo2***********//
int			check_closed_quotes(char *str);
int			check_redirect(char *str);
int			check_no_newline_flag(t_minishell *shell);
int			echo_no_args(t_minishell *shell);
int			echo_no_args2(t_minishell *shell, int i);

//***********env***********//
t_list		*get_env_vars(char **env);
t_env		*create_env_node(char *env);
char		*get_var_name(char *env);
char		*get_var_value(char *env);
char		**env_copy(t_list *lst);

//***********env2**********//
int			print_env(t_minishell *shell);
void		free_temps(char *a, char *b, char *c);

//***********execute***********//
int			execute_single_cmd(t_minishell *shell, char *command);
int			execute_multi_cmd(t_minishell *shell, char *command, int i);
int			other_cmds(t_minishell *shell, char *command, char **command_args);
int			e_execve(t_minishell *sh, char *cmd, char **cmd_args, char *cmd_tp);
void		get_exapander_flags(t_minishell *shell, char *command);

//***********exit_utils***********//
int			ft_word_count(char **str);
int			check_arg(char *str);
long long	ft_atol(const char *str);

//***********exit_utils2***********//
char		*ft_ltoa(long long n);

//***********exit***********//
void		get_exit_status(t_minishell *shell);
int			ft_exit_status(t_minishell *shell);
int			exit_status2(t_minishell *shell, int count);
int			exit_status3(t_minishell *shell);

//***********expander***********//
void		ft_expander(t_minishell *shell);
int			expand_variable(t_minishell *shell, int i);
void		perform_var_expansion(t_minishell *shell, int i, char *after_ds);
char		*perform_var_expansion2(t_minishell *shell, char *after_ds);

//***********expander2***********//
char		*get_after_dollar(char *str);
char		*get_before_dollar(char *str);
int			check_var_true(char *str, t_minishell *shell);
char		*var_value(char *str, t_minishell *shell);
void		var_false(t_minishell *shell, int i, char *after_ds);

//***********expander3***********//
void		not_expand1(t_minishell *shell, int i);
int			count_dollars(char *str);
void		expand_multiple(t_minishell *sh, int i, int x, int start);
char		*expand_multiple2(t_minishell *shell, char *temp, int x);
char		*expand_multiple3(char *temp);

//***********expander4***********//
char		*join_vars(t_minishell *shell, char *initial_str, char *return_str);
int			obtain_end(t_minishell *sh, int i, int *st);
void		expand_multiple_end(t_minishell *sh, int i, char *return_str);

//***********export***********//
t_list		*get_exp_vars(char **env);
t_env		*create_exp_node(char *env);
char		*get_exp_info(char *env);
char		*get_exp_name(char *env);
void		place_exp_var(t_minishell *shell, char *str);

//***********export2***********//
void		change_struct(t_minishell *shell, char *str);
int			ft_check_dup(t_minishell *shell, char *str);
int			ft_check_dup2(t_minishell *shell, char *str, char *name);
void		change_value_exp(t_minishell *shell, char *str, char *exp_name);
char		*get_temp(char *str, int i, int j);

//***********export3***********//
void		change_value_env(t_minishell *shell, char *str, char *name);
void		change_value_env2(t_minishell *shell, char *name, char *temp);
int			ft_check_dup3(t_minishell *shell, char *str);
int			ft_check_dup4(t_minishell *shell, char *str);
int			ft_check_exp(t_minishell *shell, char *str);

//***********export4***********//
int			ft_check_exp2(t_minishell *shell, char *temp2);
void		print_exp(t_minishell *shell);
char		**sort_exp(t_list *lst, t_list *head);
char		**sort_exp2(char **exp_array, int i, int size);
int			check_exp_quotes(char *original);

//***********export5***********//
int			check_exp_input(char *str);
int			check_exp_input2(char *temp);
char		*quote_remover_exp(char *original);
char		*quote_remover_exp2(char *str, char temp);

//***********free***********//
void		free_env(t_list *lst);
void		free_export(t_list *lst);
void		free_export1(t_list *lst);
void		free_struct(t_minishell *shell);
void		free_struct_multi(t_minishell *shell);

//***********free2***********//
void		free_struct_spaces(t_minishell *shell);
void		free_splited(char **array);
void		free_copies(char **copy);
void		free_eof(t_minishell *shell);
int			free_child_p(t_minishell *shell, char **cmd_args, char *command);

//***********free2***********//
int			free_child_process_multi(t_minishell *shell, char *command);

//***********multi_commands***********//
int			multi_commands(t_minishell *shell);
int			pipe_creation(t_minishell *shell);
void		through_pipes(t_minishell *shell, int i);
void		pipe_closing(t_minishell *shell);
char		*remove_last_space(char *str);

//***********pwd***********//
void		print_pwd(t_minishell *shell);

//***********redirects***********//
char		**handle_redirects(t_minishell *shell, char *command);
int			redirect_output(int i, char **args);
int			redirect_input(int i, char **args);
int			redirect_append(int i, char **args);
int			here_doc(char *delimiter);

//***********redirects2***********//
char		**place_null(int i, int num_words, char **command_args);
void		handle_output(t_minishell *sh, int i, char **cmd_args, char *cmd);
void		handle_input(t_minishell *sh, int i, char **cmd_args, char *cmd);
void		handle_append(t_minishell *sh, int i, char **cmd_args, char *cmd);
void		handle_heredoc(t_minishell *sh, int i, char **cmd_args, char *cmd);

//***********redirects3***********//
char		**double_sign(t_minishell *sh, int i, char **cmd_args, char *cmd);
void		redirect(t_minishell *shell);

//***********signals***********//
void		handle_signals(void);
void		sighand(int signal);
void		sigint_on_child(int signal);
void		signal_default(void);

//***********single_command***********//

int			single_command(t_minishell *shell);
int			single_command2(t_minishell *shell, char *command);
char		**remove_redirs(char *command, t_minishell *shell);
int			check_closed(t_minishell *shell, int i, char **com_args);
char		quote_value(char c, char quote);

//***********single_command2***********//

char		**ft_splitting(char *command, char delimiter);
int			countwords(char *str);
int			ft_wordcount_meta(char *str, char c);

//***********single_command3***********//

char		*whitespaces(char *str);
char		*whitespaces2(char *new_str, char *str, int *i, int *j);
int			strlength(char *str);
int			check_quotes_on_args(char **args, t_minishell *shell);
void		quote_on_expander(char *arg, int i, t_minishell *shell);

//***********unset***********//
void		do_unset(t_minishell *shell);
int			only_exp(char *str, t_minishell *shell);
void		unset_env(t_minishell *shell, t_list *temp, int i);
void		unset_exp(t_minishell *shell, t_list *temp, int i);
void		unset_only_exp(t_minishell *shell, t_list *temp, int i);

//***********unset2***********//
char		*adjust_name_env(char *str);
char		*adjust_name_exp(char *str);

//***********utils***********//
int			string_comp(char *s1, char *s2);
int			len_compare(char *s1, char *s2);
char		*join_quotes(char *str);
void		get_prompt(t_minishell *shell);
char		*get_prompt2(int i, int j, char *temp);

//***********utils2***********//
int			ft_search(char *str, char c);
int			counting_pipes(t_minishell *shell);
int			check_pipe1(char **verify_cmds, int i);
int			check_pipe2(char **ver_cmd, int i);
void		shell_pipes_count(t_minishell *shell, int i, int flag, char ignore);

//***********utils3***********//
int			check_available_paths(t_list *env);
int			check_equal(char *str, int i);
int			check_equal2(char *str, int i, int count);
int			check_args(char **command, t_minishell *shell);
int			check_args2(int *x, char **cmd, char *str, t_minishell *shell);

//***********utils4***********//
void		check_export_args(t_minishell *shell);
int			check_pipe(int i, char **verify_cmds, int num_words);

#endif