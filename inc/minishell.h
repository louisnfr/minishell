/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 04:18:31 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** librairies
*/
# include "libft.h"
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

# include "turtle.h"
# include "struct.h"
# include "enum.h"

# ifdef __linux__
#  include <linux/kd.h>
# endif

/*
** structures
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_value;
	struct s_env	*next;
}	t_env;

typedef int	t_bool;

typedef enum s_boolean
{
	CHILD	= 0,
	FAIL	= 0,
	SUCCESS = 1,
}	t_boolean;

typedef enum s_delimiter
{
	PIPE				= 1,
	AND					= 2,
	OR					= 3,
	SEMICOLON			= 4,
	LEFT_MARK			= 5,
	HEREDOC				= 6,
	RIGHT_MARK			= 7,
	DOUBLE_RIGHT_MARK	= 8,
}	t_delimiter;

typedef struct s_cmd
{
	int				input;
	int				output;
	char			*command;
	char			**options;
	char			**args;
	char			*path;
	t_bool			is_builtin;
	int				delimiter;
	struct s_cmd	*next;
	char			*heredoc;
	char			*heredoc_delimiter;
}			t_cmd;

typedef struct s_data
{
	t_cmd	*cmd_list;
	t_env	*env;
	char	**all_paths;
	int		i;
	int		ret_value;
	pid_t	pid;
	char	*tab_delimiters;
}	t_data;

/*
** builtin
*/
t_bool	exec_echo(t_cmd *cmd_list, t_data *data);
t_bool	exec_cd(t_cmd *cmd_list, t_data *data);
t_bool	exec_pwd(t_cmd *cmd_list, t_data *data);
t_bool	exec_env(t_cmd *cmd_list, t_data *data);
t_bool	exec_export(t_cmd *cmd_list, t_data *data);
t_bool	exec_unset(t_cmd *cmd_list, t_data *data);
void	exec_exit(t_cmd *cmd_list, t_data *data);
/*
** shell
*/
char	*prompt(void);
/*
** shell/env
*/
t_env	*create_env(char **envp);
void	update_env(t_data *data);
char	*get_env(char *key, t_data *data);
void	set_env(char *key, char *new_value, t_data *data);
t_env	*new_var(char *name, char *value, int is_value);
t_env	*get_last(t_env *g_env);
void	add_var(t_env **g_env, t_env *new_var);
void	print_env(t_env *g_env);
/*
** shell/exec
*/
int		exec(char **envp, t_data *data);
t_bool	exec_builtin(t_cmd *cmd_list, t_data *data);
t_bool	exec_command(pid_t pid, char **envp, t_cmd *cmd_list, t_data *data);
char	**fill_cmd_array(t_cmd *cmd_list);
int		exec_pipes(char **envp, t_cmd **cmd_list, t_data *data);
void	close_all_fd(t_data *data);
void	close_fd(t_cmd **cmd_list);
void	exit_error_with_msg(char *error_msg, char *errno_msg, t_data *data);
/*
** libft
*/
int		ft_str_isdigit(char *s);
int		ft_isspace(int c);
int		str_is_equal(const char *s1, const char *s2);
void	clean_free(char **str);
char	*ft_strjoin_and_free(char *s1, char *s2);
void	free_double_str(char **str);
char	**ft_split_on_first(const char *s, char c);
/*
** linked_list
*/
void	setup_cmd_list(t_cmd *cmd_list);
void	clean_cmd_list(t_cmd *cmd_list);
t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list);
void	print_list(t_cmd *cmd_list);
/*
** parsing
*/
char	**get_paths(char **envp);
/*
** parsing/parse_input
*/
t_bool	parse(char *input, t_data *data);
char	*find_cmd_path(char *command, char **all_paths);
char	**find_cmd_options(char **argv, t_data *data);
char	**find_cmd_args(char **argv, t_data *data);
t_bool	cmd_is_builtin(char *cmd);
t_bool	is_delimiter(char *str);
int		get_delimiter(char *str);
t_bool	is_redirection(int delimiter);
void	handle_redirection(int delimiter, t_cmd *cmd_list);
/*
** parsing/upgrade_input
*/
char	*check_input(char *input);
char	*upgrade_input(char *input, t_data *data);
char	*parse_env_variable(char *input, t_data *data);
int		is_charset_env(char c);
char	*get_env_value(char *str, int *i, t_data *data);
char	*get_env_key(char *str, int *i);
int		get_length_env_value(char *env_key, t_data *data);
int		get_length_new_input(char *str, t_data *data);
char	*transform_special_value(char *str, char *value, char character);
/*
** parsing/split_input
*/
char	**split_input(char *str, t_data *data);
int		split_count_words(char *str, t_data *data);
int		is_charset_split(char c);
int		is_delimiter_split(char c);
int		is_other_delimiter(char c1, char c2, char delimiter);
int		check_multiple_delimiters(
			char *str, int j, t_data *data);
int		display_error_msg_delimiter(int count, char delimiter);
int		handle_delimiters(int i, char **str, char **strs);
int		check_delimiter(char *str, char delimiter, int *i, int *words, t_data *data);
int		check_error_delimiter(int j, char *str, int delimiter, t_data *data);
/*
** parsing/pipes
*/
void	parse_pipes(t_cmd *cmd_list);
/*
** exit
*/
void	free_env(t_env *g_env);
void	free_split(char **args);
t_bool	cd_error(char *pwd, t_cmd *cmd_list);

#endif
