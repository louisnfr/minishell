/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:25:37 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/28 20:25:27 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include "enum.h"

/*
** parsing/utils
*/
char		**get_paths(t_data *data);
void		recheck_cmd_path(t_cmd **cmd_list, t_data *data);
void		setup_cmd_list(t_cmd *cmd_list);
void		clean_cmd_list(t_cmd **cmd_list, t_data *data);
void		create_new_cmd(t_cmd **cmd_list, t_data *data);
void		print_list(t_cmd *cmd_list);
/*
** parsing/parser
*/
t_bool		parse(char *input, t_data *data);
void		handle_bin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		handle_builtin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
char		*find_cmd_path(
				char *command, char *path, char **all_paths, t_data *data);
char		**find_cmd_options(char **argv, t_data *data);
char		**find_cmd_options_end(char **argv, t_data *data);
char		**find_cmd_args(char **argv, t_data *data);
char		**find_cmd_args_end(char **argv, char **args, t_data *data);
t_bool		cmd_is_builtin(char *cmd);
t_bool		is_delimiter(char *str);
int			get_delimiter(char *str);
t_bool		is_redirection(char *str);
t_bool		is_parenthese(char *str);
int			get_redirection(char *str);
void		parse_redirections(
				char **argv, t_cmd **cmd_list, t_data *data);
void		clean_redir(t_data *data);
void		parse_pipes(t_cmd *cmd_list, t_data *data);
void		parse_special_value(t_cmd *cmd_list, t_data *data);
void		handle_parentheses(int delimiter, char **argv, t_data *data);
void		handle_bin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		handle_builtin_cmd(
				int delimiter, char **argv, t_cmd *cmd_list, t_data *data);
void		free_fd_array(int size, int **fd_array);
void		close_cmd_pipes_fd(t_cmd **cmd_list, t_data *data);
void		parse_redirection_heredoc(
				char **argv, t_cmd *cmd_list, t_data *data);
t_redir		*parse_start_redirection(char **argv, t_data *data);
char		**copy_existing_files(
				int **copy_redir, t_cmd *cmd_list, t_data *data);
void		fill_existing_files_redir(
				int *redir, char **files, t_cmd *cmd_list, t_data *data);
int			malloc_files(
				int length, t_cmd *cmd_list, t_data *data);
void		parse_cmd(
				int delimiter, char **argv, t_cmd **cmd_list, t_data *data);
void		parse_end_cmd(
				char **argv, t_cmd **cmd_list, t_data *data);
/*
** parsing/lexer
*/
char		*parse_env_variable(char *input, t_data *data);
void		fill_env_value(
				char *new_str, t_var *var, char *str, t_data *data);
int			is_charset_env(char c);
char		*get_env_val(char *str, int *i, t_data *data);
char		*get_env_key(char *str, int *i, t_data *data);
int			get_length_env_value(
				int double_quotes, char *env_key, t_data *data);
int			get_length_new_input(char *str, t_data *data);
char		*transform_str(
				char *str, char *pid_value, char *ret_value, t_data *data);
char		*transform_pid_value(char *str, char *value, t_data *data);
char		*transform_ret_value(char *str, char *value, t_data *data);
void		handle_env_variable(
				int double_quotes, t_var *var, char *str, t_data *data);
void		fill_env_value(
				char *new_str, t_var *var, char *str, t_data *data);
void		fill_with_value(t_var *var, char *new_str, char *value);
t_var		*init_var(t_data *data);
void		free_var(t_var *var);
int			setup_variables(int *i, int *count, int *double_quotes, char *str);
void		increment_var(int *i, int *length);
void		increment_i_j(t_var *var);
/*
** parsing/split
*/
char		**split_input(char *str, t_data *data);
int			split_count_words(char *str, t_data *data);
t_bool		malloc_strs(int i, char **str, char **strs, t_data *data);
int			is_charset_split(char c);
int			is_delimiter_split(char c);
void		count_in_quotes_split(int *j, char *tmp);
void		fill_quotes_split(char **str, char **strs, int *i, int *j);
/*
** parsing/checker
*/
char		*check_input(char *input, t_data *data);
void		*display_error_msg_simple_dot(char **str);
int			check_delimiter(
				char *str, char delimiter, int *words, t_data *data);
int			check_multiple_delimiters(
				char *str, int j, t_data *data);
int			display_error_msg_delimiter(int count, char delimiter);
t_bool		check_beginning(char *str, int i);
t_bool		check_error_redir(char *str, int *i);
int			is_error_redir(char *str, int j);
int			check_right_marks(char *str, int j);
int			check_left_marks(char *str, int j);
char		**check_argv(char **argv, t_data *data);
t_bool		check_unclosed_quotes(char *input);
t_bool		check_unclosed_parentheses(char *input);
int			get_length_new_argv(char **argv);
t_bool		fill_new_argv(
				int length, char **argv, char **new_argv, t_data *data);
/*
** parsing/heredoc
*/
t_bool		process_ctrl_key_hd(
				t_data *data, t_config *sh, char *delimiter, int c);
char		*heredoc_process_keypress(
				t_data *data, t_config *sh, t_history *hist, char *delimiter);
t_bool		process_ctrl_d_heredoc(
				t_data *data, t_config *sh, char *delimiter);
void		process_ctrl_l_heredoc(t_config *sh);
t_bool		process_ctrl_c_heredoc(t_data *data, t_config *sh);
char		*heredoc_shell(
				t_data *data, t_config *sh, t_history *hist, char *delimiter);
t_bool		read_heredoc(t_bool quotes, t_cmd *cmd_list, t_data *data);
char		*heredoc_env_variable(char *input, t_data *data);
char		*heredoc_special_value(
				char *str, char *value, char character, t_data *data);
t_bool		handle_heredoc_quotes(
				int *i, char **str, char **strs, t_data *data);

#endif
