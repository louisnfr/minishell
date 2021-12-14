/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 12:33:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*** librairies ***/

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
# include "builtins.h"
# include "shell.h"
# include "parsing.h"
# include "env.h"

# ifdef __linux__
#  include <linux/kd.h>
# endif

/*** init ***/

t_bool	init_cmd_list(t_data *data, char *input);
t_data	*init_data(char **envp);

/*** clean ***/

void	clean_data(t_data *data);
void	exit_error_str(char *str, char *error, t_data *data);
void	exit_error_strs(char **strs, char *error, t_data *data);
void	exit_error_child(char **strs, char **strs2, char *error, t_data *data);
void	exit_error_fd_array(int **fd_array, int nb_of_pipes, t_data *data);
void	free_pipe_heredoc(t_data *data);
void	clean_free_double_str(int nb_of_str, t_cmd **cmd_list);
void	free_args(int nb_of_str, char **args);
void	free_inputs(char **input, t_data *data);
int		check_raw_input(char *input);

/*** protected functions ***/

char	*safe_strdup(char *str, t_data *data);
char	*safe_strdup_free(char *str, t_data *data, char **strs);
char	**safe_split(const char *str, char c, t_data *data);
char	**safe_split_on_first(char *str, char c, t_data *data);
char	*safe_strjoin(char *s1, char *s2, t_data *data);
char	*safe_strjoin_and_free(char *s1, char *s2, t_data *data);
char	*safe_strjoin_and_free2(char *s1, char *s2, t_data *data, char **strs);
char	*safe_itoa(int n, t_data *data);
char	*safe_substr(char *str, int start, int len, t_data *data);
t_bool	safe_close_fd(int fd, pid_t *pid, t_data *data);
char	**safe_double_strdup(
			char **str, int size, t_cmd *cmd_list, t_data *data);
char	*safe_getcwd(t_data *data);

/*** exec ***/

int		exec(t_data *data);
t_bool	init_exec(
			int *exit_code, int *error_file, t_cmd **cmd_list, t_data *data);
t_bool	open_files(int *exit_code, t_cmd *cmd_list, t_data *data);
void	display_error_redir(int fd, char *filename, char *errno_msg);
void	handle_ambiguous_redir(int *error, int i, t_cmd *cmd_list);
void	handle_bin_command(int *exit_code, t_cmd **cmd_list, t_data *data);
t_bool	error_bin_cmd(
			char *error_msg, int exit_code, t_cmd **cmd_list, t_data *data);
char	**fill_cmd_array(t_cmd *cmd_list, t_data *data);
int		exec_pipes(t_cmd **cmd_list, t_data *data);
void	close_all_fd(pid_t *pid, t_data *data);
void	close_fd(t_cmd **cmd_list, pid_t *pid, t_data *data);
int		get_error_code(void);
t_bool	count_wildcard_arg(int *i, char *wildcard_arg);
t_bool	fill_wildcard_arg(
			char **cmd_array, int *i, char *wildcard_arg, t_data *data);
int		matching_name(char *filename, char *wildcard);
t_bool	update_path(int *exit_code, t_cmd **cmd_list, t_data *data);
t_bool	handle_execution(int *exit_code, t_cmd **cmd_list, t_data *data);
void	handle_error_msg_exec(int *exit_code, char *command, int fd_error);
void	check_exit_code(int exit_code, t_cmd **cmd_list, t_data *data);
void	get_next_cmd(t_cmd **cmd_list, t_data *data);
int		handle_error_cmd_pipe(t_cmd **cmd_list);
void	close_pipe(t_cmd **cmd, pid_t *pid, t_data *data);
void	close_other_pipes(t_cmd **cmd, pid_t *pid, t_data *data);
void	close_all_pipes(t_cmd **cmd, pid_t *pid, t_data *data);
t_bool	create_fork(int i, pid_t *pid, t_cmd **cmd_list, t_data *data);
void	init_fd(int fd, t_data **data);
void	exit_error_pipes(t_cmd **cmd_list, t_data *data);

/*** exec/parentheses ***/

int		exec_parentheses(int exit_code, t_cmd **cmd_list, t_data *data);
void	check_redir_parentheses(t_cmd *cmd_list, t_data *data);
t_bool	check_exec_parentheses(
			int last_exit_code, t_cmd **cmd_list, t_data *data);
int		get_num_parenthese(t_cmd *cmd_list);
void	close_fd_parentheses(t_cmd **cmd_list, t_data *data);
t_bool	copy_last_file(char	*file, t_cmd **cmd_list, t_data *data);
t_bool	copy_last_redirection(
			t_bool is_first, int redirection, t_cmd **cmd_list);
void	change_last_redirection(t_cmd **cmd_list);

/*** exit ***/

void	free_env(t_env *env);
void	free_split(char **args);
void	free_history(t_hist *hist);
void	display_error_message(char *cmd, char *errno_msg, int fd);
void	syntax_error_char_msg(int nb, char token);
char	**syntax_error_str_msg(char *token, char **str);

/*** utils ***/

char	**copy_strs_and_free(char **strs, t_data *data, char **free);
char	**copy_strs(char **strs, t_data *data);
t_bool	str_is_in_str(char *s1, char *s2);
int		ctrl_key(int k);

#endif
