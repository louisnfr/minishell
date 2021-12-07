/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:07:14 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/06 23:34:15 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_input(t_confg *sh, t_hist *hist, int c)
{
	sh->cx_max++;
	if (sh->search == sh->h_num)
	{
		sh->current = insert_char(sh->current, sh->cx, (char)c);
		write(1, "\x1b[s", 3);
		clear_prompt(sh->cx, ft_strlen(sh->current));
		write(1, sh->current, ft_strlen(sh->current));
		write(1, "\x1b[u", 3);
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
	else
	{
		write(1, "\x1b[s", 3);
		insert_char_history(sh->history, sh->cx, (char)c, sh->search);
		sh->input = ft_realloc(sh->input, sizeof(char)
				* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
		ft_strcpy(sh->input, find_cmd_history(hist, sh->search));
		clear_prompt(sh->cx, ft_strlen(sh->input));
		write(1, sh->input, ft_strlen(sh->input));
		write(1, "\x1b[u", 3);
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
}

char	*send_cmd(t_confg *sh)
{
	if (sh->current && sh->search == sh->h_num)
		return (sh->current);
	return (sh->input);
}

char	*shell_process_keypress(t_data *data, t_confg *sh, t_hist *hist)
{
	int	c;

	c = 0;
	init_shell_values(sh);
	while (c != 13)
	{
		c = read_key(sh, data);
		if (c == ctrl_key('c') || c == ctrl_key('d')
			|| c == ctrl_key('u') || c == ctrl_key('l'))
		{
			if (!process_ctrl_key(data, sh, hist, c))
				return (NULL);
		}
		else if (c == TAB_KEY)
			process_tab_key(sh, data);
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
