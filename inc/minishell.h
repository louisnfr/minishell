/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 22:32:20 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** librairies
*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <term.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <dirent.h>

# include "libft.h"
# include "enum.h"
# include "struct.h"

# ifdef __linux__
#  include <linux/kd.h>
# endif

/*
** init
*/
t_bool		init_cmd_list(t_data *data);
t_data		*init_data(char **envp);
/*
** clean
*/
void		clean_data(t_data *data);
/*
** builtin
*/
t_bool		exec_echo(t_cmd *cmd_list, t_data *data);
t_bool		exec_cd(t_cmd *cmd_list, t_data *data);
t_bool		exec_pwd(t_cmd *cmd_list, t_data *data);
t_bool		exec_env(t_cmd *cmd_list, t_data *data);
t_bool		exec_history(t_cmd *cmd_list, t_data *data);
t_bool		exec_export(t_cmd *cmd_list, t_data *data);
t_bool		exec_unset(t_cmd *cmd_list, t_data *data);
void		exec_exit(t_cmd *cmd_list, t_data *data);
/*
** shell
*/
char		*prompt(t_data *data);
void		display_error_message(char *cmd, char *errno_msg, int fd);
void		syntax_error_char_msg(int nb, char token);
char		**syntax_error_str_msg(char *token, char **str);
/*
** shell/env
*/
int			get_env_size(t_env *env);
char		**env_to_char(t_env *env);
t_env		*create_env(char **envp);
void		update_env(t_data *data);
char		*get_env(char *key, t_env *env);
void		set_env(char *key, char *new_value, t_env *env);
t_env		*new_var(char *name, char *value, int is_value);
t_env		*get_last(t_env *g_env);
void		add_var(t_env **g_env, t_env *new_var);
void		print_env(t_env *g_env, t_cmd *cmd_list);
/*
** shell/exec
*/
int			exec(t_data *data);
t_bool		exec_builtin(t_cmd *cmd_list, t_data *data);
t_bool		exec_bin_command(pid_t *pid, t_cmd *cmd_list, t_data *data);
t_bool		error_bin_cmd(
				char *error_msg, int exit_code, t_cmd *cmd_list, t_data *data);
char		**fill_cmd_array(t_cmd *cmd_list, t_data *data);
int			exec_pipes(t_cmd **cmd_list, t_data *data);
void		close_all_fd(t_data *data);
void		close_fd(t_cmd **cmd_list);
void		exit_error_with_msg(char *error_msg, char *errno_msg, t_data *data);
int			get_error_code(void);
t_bool		count_wildcard_arg(int *i, char *wildcard_arg);
t_bool		fill_wildcard_arg(char **cmd_array, int *i, char *wildcard_arg);
int			matching_name(char *filename, char *wildcard);
void		update_path(t_cmd **cmd_list, t_data *data);
t_bool		handle_execution(int *exit_code, t_cmd **cmd_list, t_data *data);
int			exec_parentheses(int exit_code, t_cmd **cmd_list, t_data *data);
void		handle_error_msg_exec(int *exit_code, char *command, int fd_error);
void		check_exit_code(int exit_code, t_cmd **cmd_list);
t_bool		is_first_pipe(t_cmd *cmd_list);
t_bool		is_last_pipe(t_cmd *cmd_list);
int			handle_error_cmd_pipe(t_cmd **cmd_list);
void		close_pipe(t_cmd **cmd);
void		close_other_pipes(t_cmd **cmd);
void		close_all_pipes(t_cmd **cmd);
t_bool		create_fork(int i, pid_t *pid);
/*
** libft
*/
int			ft_str_isdigit(char *s);
int			ft_isspace(int c);
int			str_is_equal(const char *s1, const char *s2);
void		clean_free(char **str);
char		*ft_strjoin_and_free(char *s1, char *s2);
void		free_double_str(char **str);
char		**ft_split_on_first(const char *s, char c);
/*
** parsing/utils
*/
char		**get_paths(t_data *data);
void		setup_cmd_list(t_cmd *cmd_list);
void		clean_cmd_list(t_cmd **cmd_list);
t_bool		create_new_cmd(
				char *cmd, char **options, char *path, t_cmd **cmd_list);
void		print_list(t_cmd *cmd_list);

/*
** parsing/parser
*/
t_bool		parse(char *input, t_data *data);
void		handle_bin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		handle_builtin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
char		*find_cmd_path(char *command, char *path, char **all_paths);
char		**find_cmd_options(char **argv, t_data *data);
char		**find_cmd_options_end(char **argv, t_data *data);
char		**find_cmd_args(char **argv, t_data *data);
t_bool		cmd_is_builtin(char *cmd);
t_bool		is_delimiter(char *str);
int			get_delimiter(char *str);
t_bool		is_redirection(char *str);
t_bool		is_parenthese(char *str);
int			get_redirection(char *str);
void		parse_redirections(char **argv, t_cmd *cmd_list, t_data *data);
void		display_error_redir(int fd, char *filename, char *errno_msg);
void		parse_pipes(t_cmd *cmd_list);
void		parse_special_value(t_cmd *cmd_list, t_data *data);
void		handle_parentheses(int delimiter, char **argv, t_data *data);
void		handle_bin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		handle_builtin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		free_fd_array(int size, int **fd_array);
void		close_cmd_pipes_fd(t_cmd **cmd_list);
void		parse_redirections_heredoc(
				char **argv, t_cmd *cmd_list, t_data *data);
/*
** parsing/lexer
*/
char		*upgrade_input(char *input, t_data *data);
char		*parse_env_variable(char *input, t_data *data);
int			is_charset_env(char c);
char		*get_env_val(char *str, int *i, t_data *data);
char		*get_env_key(char *str, int *i);
int			get_length_env_value(
				int *double_quotes, char *env_key, t_data *data);
int			get_length_new_input(char *str, t_data *data);
char		*transform_pid_value(char *str, char *value);
char		*transform_ret_value(char *str, char *value);
void		handle_env_variable(
				int *double_quotes, t_var *var, char *str, t_data *data);
void		fill_env_value(
				int *double_quotes, char *new_str, t_var *var, char *value);
void		fill_with_value(t_var *var, char *new_str, char *value);
t_var		*init_var(void);
void		free_var(t_var *var);
int			setup_variables(int *i, int *count, int *double_quotes, char *str);
void		increment_var(int *i, int *length);
void		increment_i_j(t_var *var);
char		*handle_equal_sign(char *input, t_data *data);
/*
** parsing/split
*/
char		**split_input(char *str);
int			split_count_words(char *str);
int			is_charset_split(char c);
int			is_delimiter_split(char c);
int			handle_delimiters(int i, char **str, char **strs);
void		count_in_quotes_split(int *j, char *tmp);
void		fill_quotes_split(char **str, char **strs, int *i, int *j);
/*
** parsing/checker
*/
char		*check_input(char *input);
void		*display_error_msg_simple_dot(char **str);
int			check_delimiter(
				char *str, char delimiter, int *i, int *words);
int			check_error_delimiter(
				int j, char *str, int delimiter);
int			check_multiple_delimiters(
				char *str, int j);
int			display_error_msg_delimiter(int count, char delimiter);
t_bool		check_beginning(char *str, int *i);
t_bool		check_error_redir(char *str, int *i);
int			is_error_redir(char *str, int j);
int			check_right_marks(char *str, int j);
int			check_left_marks(char *str, int j);
char		**check_argv(char **argv);
t_bool		check_unclosed_quotes(char *input);
t_bool		check_unclosed_parentheses(char *input);
/*
** parsing/heredoc
*/
char		*heredoc_shell(
				t_data *data, t_config *sh, t_history *hist, char *delimiter);
t_bool		read_heredoc(t_bool quotes, t_cmd *cmd_list, t_data *data);
char		*heredoc_env_variable(char *input, t_data *data);
char		*heredoc_special_value(char *str, char *value, char character);
t_bool		handle_heredoc_quotes(int *i, char **str, char **strs);
/*
** exit
*/
void		free_env(t_env *g_env);
void		free_split(char **args);
t_bool		cd_error(t_cmd *cmd_list);
t_bool		cd_error_msg(char *s, t_cmd *cmd_list);

/*** TURTLE FUNCTIONS ***/

/*** raw ***/

void		disable_raw_mode(t_config *sh);
void		enable_raw_mode(t_config *sh);
void		enable_heredoc_raw_mode(t_config *sh);
void		init_shell(t_config *sh);

/*** shell ***/

/*** erase_char ***/

void		erase_char(char *s, int cx);
void		erase_char_history(t_history *hist, int cx, int search);
void		erase_cmd_history(char *input, t_history *history, int search);

/*** erase_keys ***/

void		erase_char_current(t_config *sh);
void		erase_char_input(t_config *sh, t_history *hist);
void		process_del_key(t_config *sh, t_history *hist);
void		process_backspace_key(t_config *sh, t_history *hist);

/*** read ***/

int			read_key(t_config *sh);
int			read_escape_seq(void);
int			read_arrow_key(char c);

/*** tab ***/

void		process_tab_key(t_config *sh);

/*** arrows ***/

void		process_arrow_key(t_config *sh, t_history *hist, int c);
void		move_cursor_left(t_config *sh);
void		move_cursor_right(t_config *sh);
void		process_arrow_up(t_config *sh, t_history *hist);
void		process_arrow_down(t_config *sh, t_history *hist);

/*** ctrl_keys ***/

t_bool		process_ctrl_key(t_data *data, t_config *sh, t_history *hst, int c);
void		process_ctrl_d(t_config *sh, t_history *hist);
t_bool		process_ctrl_c(t_config *sh);
void		process_ctrl_l(t_config *sh, t_data *data);
void		process_ctrl_u(t_config *sh, t_history *hist);

void		setup_prompt(char **input, t_data *data);
int			read_key(t_config *sh);
char		*heredoc_process_keypress(
				t_data *data, t_config *sh, t_history *hist, char *delimiter);
char		*shell_process_keypress(
				t_data *data, t_config *sh, t_history *hist);
int			get_pos_cursor(int *cx, int *cy);

/*** init ***/

void		init_shell_values(t_config *sh);
void		init_shell(t_config *sh);
t_config	*init_config(char **envp);
t_history	*init_history(void);

/*** lists ***/

t_history	*new_cmd(char *cmd, int num);
t_history	*getlast(t_history *hist);
void		add_cmd(t_history **hist, t_history *new);

/*** insert_char ***/
void		insert_char_history(t_history *hist, int cx, char c, int search);
char		*insert_char(char *current, int cx, char c);

char		*find_cmd_history(t_history *hist, int h_num);
void		print_history(t_history *hist);
void		clear_hist(t_history *hist, int search);

/*** utils ***/

int			ctrl_key(int k);
void		clear_prompt(int cx, int len);
char		*ft_strjoin(char *s1, char *s2);

/*** exit ***/

void		exit_error(const char *s, t_config *sh);
void		exit_free(t_config *sh, t_history *hist);
void		free_history(t_history *hist);

#endif
