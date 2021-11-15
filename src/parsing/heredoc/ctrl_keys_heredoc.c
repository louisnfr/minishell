/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:18:26 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/15 19:47:34 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	process_ctrl_key_hd(t_data *data, t_config *sh, char *delimiter, int c)
{
	if (c == ctrl_key('d'))
		return (!process_ctrl_d_heredoc(data, sh, delimiter));
	else if (c == ctrl_key('c'))
		return (process_ctrl_c(sh));
	else if (c == ctrl_key('l'))
		process_ctrl_l_heredoc(sh, data);
	else if (c == ctrl_key('u'))
		process_ctrl_u(sh, sh->history);
	return (SUCCESS);
}

t_bool	process_ctrl_d_heredoc(t_data *data, t_config *sh, char *delimiter)
{
	(void)data;
	if ((sh->search == sh->h_num && (!sh->current || !ft_strlen(sh->current)))
		|| (sh->search != sh->h_num && (!sh->input || !ft_strlen(sh->input))))
	{
		write(1, "warning: here-document delimited by end-of-file wanted `",
			56);
		write(1, delimiter, ft_strlen(delimiter));
		write(1, "')", 2);
		return (SUCCESS);
	}
	return (FAIL);
}

void	process_ctrl_l_heredoc(t_config *sh, t_data *data)
{
	write(1, "\x1b[s", 3);
	write(1, "\x1b[2J", 4);
	write(1, "\x1b[H", 3);
	write(1, data->prpt, ft_strlen(data->prpt));
	if (sh->current && sh->search == sh->h_num)
		write(1, sh->current, ft_strlen(sh->current));
	else
		write(1, sh->input, ft_strlen(sh->input));
	write(1, "\x1b[u", 3);
	write(1, "\x1b[999A", 6);
}
