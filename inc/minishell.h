/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 14:58:57 by lraffin          ###   ########.fr       */
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
** structures
*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;

}	t_data;
/*
** builtin
*/
void	exec_echo(char **cmd, t_data *data);
void	exec_cd(char **cmd, t_data *data);
void	exec_pwd(char **cmd, t_data *data);
void	exec_env(char **cmd, t_data *data);
void	exec_export(char **cmd, t_data *data);
void	exec_unset(char **cmd, t_data *data);
void	exec_exit(char **cmd, t_data *data);
/*
** shell
*/
void	prompt(void);
/*
** shell/env
*/
t_env	*create_env(char **envp);
void	update_env(t_data *data);
char	*get_env(char *key, t_data *data);
void	set_env(char *key, char *new_value, t_data *data);
t_env	*new_var(char *name, char *value);
t_env	*get_last(t_env *g_env);
void	add_var(t_env **g_env, t_env *new_var);
void	print_env(t_env *g_env);
/*
** shell/exec
*/
void	exec(char **cmd, t_data *data);
void	exec_builtin(char **cmd, t_data *data);
/*
** parsing
*/
void	parse(char *input, t_data *data);
char	*is_builtin(char *cmd);
/*
** exit
*/
void	free_env(t_env *g_env);
void	free_split(char **args);
void	cd_error(char *pwd, char **cmd);

#endif
