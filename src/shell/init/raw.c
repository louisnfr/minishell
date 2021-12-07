/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:45 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/06 23:31:17 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_raw_mode(t_confg *sh)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->orig_termios);
}

t_bool	enable_raw_mode(t_confg *sh)
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

void	enable_heredoc_raw_mode(t_confg *sh)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &sh->orig_termios);
	raw = sh->orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	sh->init_termios = TRUE;
}
