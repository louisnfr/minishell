/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:52:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/07 02:48:39 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*send_cmd_hd(t_data *data, t_confg *sh)
{
	if (sh->current && sh->search == sh->h_num)
		return (sh->current);
	else if (sh->input && sh->search != sh->h_num)
		return (sh->input);
	else
	{
		sh->current = safe_strdup("", data);
		return (sh->current);
	}
}

static char	*heredoc_signal(int ret, char *delimiter)
{
	if (ret == CTRL_D)
		return (delimiter);
	else if (ret == CTRL_C)
		return (NULL);
	return (NULL);
}

static void	process_non_print(int c, t_data *data, t_confg *sh, t_hist *hist)
{
	if (c == TAB_KEY)
		process_tab_key(sh, data);
	else if (c == DELETE)
		process_del_key(sh, hist);
	else if (c == BACKSPACE)
		process_backspace_key(sh, hist);
}

char	*heredoc_process_keypress(
			t_data *data, t_confg *sh, t_hist *hist, char *delimiter)
{
	int	c;
	int	ret;

	c = 0;
	init_shell_values(sh);
	while (c != 13)
	{
		c = read_key(sh, data);
		if (c == ctrl_key('c') || c == ctrl_key('d')
			|| c == ctrl_key('u') || c == ctrl_key('l'))
		{
			ret = process_ctrl_key_hd(data, sh, delimiter, c);
			if (ret == CTRL_D || ret == CTRL_C)
				return (heredoc_signal(ret, delimiter));
		}
		else if (c == TAB_KEY || c == DELETE || c == BACKSPACE)
			process_non_print(c, data, sh, hist);
		else if (c >= ARROW_UP && c <= ARROW_RIGHT)
			process_arrow_key(sh, hist, c);
		else if (ft_isprint(c))
			update_input(sh, hist, c);
	}
	return (send_cmd_hd(data, sh));
}
