/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 01:07:28 by lraffin          ###   ########.fr       */
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
# include <term.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
** global
*/
struct s_env	*g_env;
/*
** structures
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef int	t_bool;

typedef enum t_boolean
{
	CHILD	= 0,
	FAIL	= 0,
	SUCCESS = 1,
	LEFT	= 0,
	RIGHT	= 1,
}	t_boolean;

typedef struct s_cmd
{
	char			*command;
	char			**options;
	char			*path;
	t_bool			is_builtin;
	struct s_cmd	*left;
	struct s_cmd	*right;
}			t_cmd;

typedef struct s_data
{
	t_cmd	*cmd_list;
	char	**all_paths;
}	t_data;

/*
** builtin
*/
void	exec_echo(char **cmd);
void	exec_cd(char **cmd);
void	exec_pwd(char **cmd);
void	exec_env(char **cmd);
void	exec_export(char **cmd);
void	exec_unset(char **cmd);
void	exec_exit(char **cmd);
/*
** shell
*/
void	prompt(void);
/*
** shell/env
*/
t_env	*create_env(char **envp);
void	update_env(void);
char	*get_env(char *key);
void	set_env(char *key, char *new_value);
t_env	*new_var(char *name, char *value);
t_env	*get_last(t_env *g_env);
void	add_var(t_env **g_env, t_env *new_var);
void	print_env(t_env *g_env);
/*
** shell/exec
*/
void	exec(char **cmd);
void	exec_builtin(char **cmd);
/*
** libft
*/
int		str_is_equal(const char *s1, const char *s2);
void	clean_free(char **str);
char	*ft_strjoin_and_free(char *s1, char *s2);
/*
** parsing
*/
void	init_cmd_list(t_cmd *cmd_list);
t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list);
void	print_list(t_cmd *cmd_list);
t_bool	parse(int ac, char *input, t_data *data, t_cmd *cmd_list);
char	**get_paths(char **envp);
char	*find_cmd_path(char *command, char **all_paths);
t_bool	cmd_is_builtin(char *cmd);
/*
** exit
*/
void	free_env(t_env *g_env);
void	free_split(char **args);
void	cd_error(char *pwd, char **cmd);

#endif
