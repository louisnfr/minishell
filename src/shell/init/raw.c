/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:45 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/17 10:13:40 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_raw_mode(t_config *sh)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->orig_termios) < 0)
		exit_error("tcsetattr", sh);
}

t_bool	enable_raw_mode(t_config *sh)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &sh->orig_termios) < 0)
		return (FAIL);
	raw = sh->orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0)
		return (FAIL);
	sh->init_termios = TRUE;
	return (SUCCESS);
}

void	enable_heredoc_raw_mode(t_config *sh)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &sh->orig_termios) < 0)
		exit_error("tcgetattr", sh);
	raw = sh->orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0)
		exit_error("tcsetattr", sh);
	sh->init_termios = TRUE;
}
