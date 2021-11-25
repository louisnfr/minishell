/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:17:46 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/25 00:09:17 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "struct.h"
# include "enum.h"

/*** shell ***/

void		setup_prompt(char **input, t_data *data);
void		update_input(t_config *sh, t_history *hist, int c);
char		*send_cmd(t_config *sh);

/*** init ***/

void		init_shell_values(t_config *sh);
void		init_shell(t_config *sh);
t_config	*init_config(char **envp);
t_history	*init_history(void);

/*** raw ***/

void		disable_raw_mode(t_config *sh);
t_bool		enable_raw_mode(t_config *sh);
void		enable_heredoc_raw_mode(t_config *sh);
void		init_shell(t_config *sh);

/*** read input ***/

int			read_key(t_config *sh);
int			read_escape_seq(void);
int			read_arrow_key(char c);
int			read_key(t_config *sh);
char		*shell_process_keypress(
				t_data *data, t_config *sh, t_history *hist);
char		*heredoc_process_keypress(
				t_data *data, t_config *sh, t_history *hist, char *delimiter);

/*** edit input ***/

void		insert_char_history(t_history *hist, int cx, char c, int search);
char		*insert_char(char *current, int cx, char c);

void		erase_char(char *s, int cx);
void		erase_char_history(t_history *hist, int cx, int search);
void		erase_cmd_history(char *input, t_history *history, int search);

/*** keys ***/

void		erase_char_current(t_config *sh);
void		erase_char_input(t_config *sh, t_history *hist);
void		process_del_key(t_config *sh, t_history *hist);
void		process_backspace_key(t_config *sh, t_history *hist);

void		process_tab_key(t_config *sh);

void		process_arrow_key(t_config *sh, t_history *hist, int c);
void		move_cursor_left(t_config *sh);
void		move_cursor_right(t_config *sh);
void		process_arrow_up(t_config *sh, t_history *hist);
void		process_arrow_down(t_config *sh, t_history *hist);

t_bool		process_ctrl_key(t_data *data, t_config *sh, t_history *hst, int c);
void		process_ctrl_d(t_data *data, t_config *sh);
t_bool		process_ctrl_c(t_data *data, t_config *sh);
void		process_ctrl_l(t_data *data, t_config *sh);
void		process_ctrl_u(t_config *sh, t_history *hist);

/*** lists ***/

t_history	*new_cmd(char *cmd, int num);
t_history	*getlast(t_history *hist);
void		add_cmd(t_history **hist, t_history *new);
char		*find_cmd_history(t_history *hist, int h_num);
void		print_history(t_history *hist);
void		clear_hist(t_history *hist, int search);

/*** utils ***/

int			ctrl_key(int k);
void		clear_prompt(int cx, int len);

/*** signal ***/

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_signals(t_data *data);


#endif
