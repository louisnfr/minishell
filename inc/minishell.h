/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:37:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 18:21:37 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
void	create_env(char **envp);
char	*get_env(char *arg);
void	set_env(char *var, char *value);
/*
** shell/exec
*/
void	exec(char **cmd);
void	exec_builtin(char **cmd);
/*
** parsing
*/
void	parse(char *input);
char	*is_builtin(char *cmd);
/*
** exit
*/
void	free_split(char **args);

#endif
