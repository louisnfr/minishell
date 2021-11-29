/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 23:40:44 by lraffin          ###   ########.fr       */
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

t_bool	init_cmd_list(t_data *data);
t_data	*init_data(char **envp);

/*** clean ***/

void	clean_data(t_data *data);
void	*exit_error_void(void *return_value, char *error, t_data *data);
t_bool	exit_error_bool(char *error, t_data *data);

/*** protected functions ***/

char	*safe_strdup(char *str, t_data *data);
char	**safe_split(const char *str, char c, t_data *data);
char	**safe_split_on_first(const char *str, char c, t_data *data);
char	*safe_strjoin(char *s1, char *s2, t_data *data);
char	*safe_strjoin_and_free(char *s1, char *s2, t_data *data);
char	*safe_itoa(int n, t_data *data);
t_bool	safe_unlink(char *pathname, t_data *data);
t_bool	safe_close_fd(int fd, t_data *data);
char	**safe_double_strdup(char **str, int size, t_data *data);

/*** exec ***/

int		exec(t_data *data);
t_bool	open_files(int *exit_code, t_cmd *cmd_list, t_data *data);
void	handle_bin_command(int *exit_code, t_cmd **cmd_list, t_data *data);
t_bool	error_bin_cmd(
			char *error_msg, int exit_code, t_cmd *cmd_list, t_data *data);
char	**fill_cmd_array(t_cmd *cmd_list, t_data *data);
int		exec_pipes(t_cmd **cmd_list, t_data *data);
void	close_all_fd(t_data *data);
void	close_fd(t_cmd **cmd_list, t_data *data);
int		get_error_code(void);
t_bool	count_wildcard_arg(int *i, char *wildcard_arg);
t_bool	fill_wildcard_arg(
			char **cmd_array, int *i, char *wildcard_arg, t_data *data);
int		matching_name(char *filename, char *wildcard);
void	update_path(t_cmd **cmd_list, t_data *data);
t_bool	handle_execution(int *exit_code, t_cmd **cmd_list, t_data *data);
int		exec_parentheses(int exit_code, t_cmd **cmd_list, t_data *data);
void	handle_error_msg_exec(int *exit_code, char *command, int fd_error);
void	check_exit_code(int exit_code, t_cmd **cmd_list);
int		handle_error_cmd_pipe(t_cmd **cmd_list);
void	close_pipe(t_cmd **cmd, t_data *data);
void	close_other_pipes(t_cmd **cmd, t_data *data);
void	close_all_pipes(t_cmd **cmd, t_data *data);
t_bool	create_fork(int i, pid_t *pid, t_data *data);
void	init_fd(int fd, t_data **data);
t_bool	init_exec(
			int *exit_code, int *error_file, t_cmd **cmd_list, t_data *data);
void	check_redir_parentheses(t_cmd *cmd_list, t_data *data);
t_bool	check_exec_parentheses(
			int last_exit_code, t_cmd **cmd_list, t_data *data);

/*** exit ***/

void	exit_error(const char *s, t_confg *sh);
void	free_env(t_env *g_env);
void	free_split(char **args);
void	exit_free(t_confg *sh, t_hist *hist);
void	free_history(t_hist *hist);
void	display_error_message(char *cmd, char *errno_msg, int fd);
void	syntax_error_char_msg(int nb, char token);
char	**syntax_error_str_msg(char *token, char **str);

/*** utils ***/

char	**copy_strs_and_free(char **strs, t_data *data);

#endif
