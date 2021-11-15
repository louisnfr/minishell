/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:52:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/15 19:46:55 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_process_keypress(
	t_data *data, t_config *sh, t_history *hist, char *delimiter)
{
	int	c;

	c = 0;
	init_shell_values(sh);
	while (c != 13)
	{
		c = read_key(sh);
		if (c == ctrl_key('c') || c == ctrl_key('d')
			|| c == ctrl_key('u') || c == ctrl_key('l'))
		{
			if (!process_ctrl_key_hd(data, sh, delimiter, c))
				return (delimiter);
		}
		else if (c == TAB_KEY)
			process_tab_key(sh);
		else if (c == DELETE)
			process_del_key(sh, hist);
		else if (c == BACKSPACE)
			process_backspace_key(sh, hist);
		else if (c >= ARROW_UP && c <= ARROW_RIGHT)
			process_arrow_key(sh, hist, c);
		else if (ft_isprint(c))
			update_input(sh, hist, c);
	}
	return (send_cmd(sh));
}
