/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turtle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:07:21 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 04:18:15 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURTLE_H
# define TURTLE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <errno.h>
# include "enum.h"
# include "struct.h"

# include "minishell.h"

/*** raw ***/

void		disable_raw_mode(t_config *sh);
void		enable_raw_mode(t_config *sh);
void		init_shell(t_config *sh);

/*** turtle ***/

int			shell_read_key(t_config *sh);
char		*shell_process_keypress(t_config *sh, t_history *hist);
int			get_pos_cursor(int *cx, int *cy);

/*** init ***/

void		init_shell(t_config *sh);
t_config	*init_config(char **envp);
t_history	*init_history(void);

/*** lists ***/

t_history	*new_cmd(char *cmd, int num);
t_history	*getlast(t_history *hist);
void		add_cmd(t_history **hist, t_history *new);

void		insert_char_history(t_history *hist, int cx, char c, int search);
void		del_char_history(t_history *hist, int cx, int search);

char		*insert_char(char *current, int cx, char c);
void		delete_char(char *s, int cx);

char		*find_cmd_history(t_history *hist, int h_num);
void		print_history(t_history *hist);
void		clear_hist(t_history *hist, int search);

/*** utils ***/

int			ctrl_key(int k);
void		clear_prompt(void);
char		*ft_strjoin(char *s1, char *s2);

/*** exit ***/

void		exit_error(const char *s, t_config *sh);
void		exit_free(t_config *sh, t_history *hist);
void		free_history(t_history *hist);

#endif
