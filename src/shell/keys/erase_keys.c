/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:39:02 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/30 19:08:17 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_del_key(t_confg *sh, t_hist *hist)
{
	if (sh->cx >= 0 && sh->cx < sh->cx_max)
	{
		if (sh->search == sh->h_num)
		{
			write(1, "\x1b[1C", 4);
			sh->cx++;
			erase_char_current(sh);
		}
		else
		{
			write(1, "\x1b[1C", 4);
			sh->cx++;
			erase_char_input(sh, hist);
		}
		sh->cx_max--;
		sh->cx--;
	}
}

void	process_backspace_key(t_confg *sh, t_hist *hist)
{
	if (sh->cx > 0)
	{
		if (sh->search == sh->h_num)
			erase_char_current(sh);
		else
			erase_char_input(sh, hist);
		sh->cx_max--;
		sh->cx--;
	}
}

void	erase_char_current(t_confg *sh)
{
	erase_char(sh->current, sh->cx - 1);
	if (!ft_strlen(sh->current))
		clean_free(&sh->current);
	write(1, "\x1b[s", 3);
	clear_prompt(sh->cx, ft_strlen(sh->current));
	write(1, sh->current, ft_strlen(sh->current));
	write(1, "\x1b[u", 3);
	write(1, "\x1b[1D", 4);
}

void	erase_char_input(t_confg *sh, t_hist *hist)
{
	write(1, "\x1b[s", 3);
	erase_char_history(sh->history, sh->cx, sh->search);
	sh->input = ft_realloc(sh->input, sizeof(char)
			* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
	ft_strcpy(sh->input, find_cmd_history(hist, sh->search));
	if (!ft_strlen(sh->input))
		clean_free(&sh->input);
	clear_prompt(sh->cx, ft_strlen(sh->input));
	write(1, sh->input, ft_strlen(sh->input));
	write(1, "\x1b[u", 3);
	write(1, "\x1b[1D", 4);
}
