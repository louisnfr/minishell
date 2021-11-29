/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:17:46 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 23:21:31 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "struct.h"
# include "enum.h"

/*** shell ***/

void	setup_prompt(char **input, t_data *data);
void	update_input(t_confg *sh, t_hist *hist, int c);
char	*send_cmd(t_confg *sh);

/*** init ***/

void	init_shell_values(t_confg *sh);
void	init_shell(t_confg *sh);
t_confg	*init_config(char **envp);
t_hist	*init_history(void);

/*** raw ***/

void	disable_raw_mode(t_confg *sh);
t_bool	enable_raw_mode(t_confg *sh);
void	enable_heredoc_raw_mode(t_confg *sh);
void	init_shell(t_confg *sh);

/*** read input ***/

int		read_key(t_confg *sh);
char	*shell_process_keypress(t_data *data, t_confg *sh, t_hist *hist);
char	*heredoc_process_keypress(
			t_data *data, t_confg *sh, t_hist *hist, char *delimiter);

/*** edit input ***/

void	insert_char_history(t_hist *hist, int cx, char c, int search);
char	*insert_char(char *current, int cx, char c);

void	erase_char(char *s, int cx);
void	erase_char_history(t_hist *hist, int cx, int search);
void	erase_cmd_history(char *input, t_hist *history, int search);

/*** keys ***/

void	erase_char_current(t_confg *sh);
void	erase_char_input(t_confg *sh, t_hist *hist);
void	process_del_key(t_confg *sh, t_hist *hist);
void	process_backspace_key(t_confg *sh, t_hist *hist);

void	process_tab_key(t_confg *sh);

void	process_arrow_key(t_confg *sh, t_hist *hist, int c);

t_bool	process_ctrl_key(t_data *data, t_confg *sh, t_hist *hst, int c);
void	process_ctrl_u(t_confg *sh, t_hist *hist);

/*** signals ***/

void	handle_sig(int sig);
void	init_signals(t_data *data);
void	handle_status(int status, int *exit_code);

/*** heredoc ***/

t_bool	process_ctrl_key_hd(t_data *data, t_confg *sh, char *delimiter, int c);
char	*heredoc_process_keypress(
			t_data *data, t_confg *sh, t_hist *hist, char *delimiter);
char	*heredoc_shell(
			t_data *data, t_confg *sh, t_hist *hist, char *delimiter);
t_bool	read_heredoc(t_bool quotes, t_cmd *cmd_list, t_data *data);
char	*heredoc_env_variable(char *input, t_data *data);
char	*heredoc_special_value(
			char *str, char *value, char character, t_data *data);
t_bool	handle_heredoc_quotes(int *i, char **str, char **strs, t_data *data);

/*** lists ***/

t_hist	*new_cmd(char *cmd, int num);
t_hist	*getlast(t_hist *hist);
void	add_cmd(t_hist **hist, t_hist *new);
char	*find_cmd_history(t_hist *hist, int h_num);
void	print_history(t_hist *hist);
void	clear_hist(t_hist *hist, int search);

/*** utils ***/

int		ctrl_key(int k);
void	clear_prompt(int cx, int len);
int		is_sep(int c);
char	*selected_input(t_confg *sh);

#endif
