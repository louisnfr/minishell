/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:26:09 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/08 15:02:07 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_cursor_left(t_confg *sh)
{
	if (sh->cx > sh->cx_min)
	{
		write(1, "\x1b[1D", 4);
		sh->cx--;
	}
}

static void	move_cursor_right(t_confg *sh)
{
	if (sh->cx < sh->cx_max)
	{
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
}

static void	process_arrow_up(t_confg *sh, t_hist *hist)
{
	sh->prev_cmd = find_cmd_history(hist, sh->search - 1);
	if (sh->prev_cmd)
	{
		sh->search--;
		if (sh->input)
			clean_free(&sh->input);
		sh->input = ft_calloc(1, sizeof(char) * (ft_strlen(sh->prev_cmd) + 1));
		if (!sh->input)
			return ;
		ft_strcpy(sh->input, sh->prev_cmd);
		clear_prompt(sh->cx, ft_strlen(sh->prev_cmd));
		write(1, sh->input, ft_strlen(sh->input));
		sh->cx = ft_strlen(sh->input);
		sh->cx_max = ft_strlen(sh->input);
	}
}

static void	process_arrow_down(t_confg *sh, t_hist *hist)
{
	sh->next_cmd = find_cmd_history(hist, sh->search + 1);
	clear_prompt(sh->cx, ft_strlen(sh->next_cmd));
	if (sh->next_cmd)
	{
		if (sh->input)
			clean_free(&sh->input);
		sh->input = ft_calloc(1, sizeof(char) * (ft_strlen(sh->next_cmd) + 1));
		if (!sh->input)
			return ;
		ft_strcpy(sh->input, sh->next_cmd);
		write(1, sh->input, ft_strlen(sh->input));
		sh->cx = ft_strlen(sh->input);
		sh->cx_max = ft_strlen(sh->input);
	}
	else if (!sh->next_cmd)
	{
		clean_free(&sh->input);
		sh->input = NULL;
		if (sh->current)
			write(1, sh->current, ft_strlen(sh->current));
		sh->cx = ft_strlen(sh->current);
		sh->cx_max = ft_strlen(sh->current);
	}
	sh->search++;
}

void	process_arrow_key(t_confg *sh, t_hist *hist, int c)
{
	if (c == ARROW_LEFT)
		move_cursor_left(sh);
	else if (c == ARROW_RIGHT)
		move_cursor_right(sh);
	else if (c == ARROW_UP)
		process_arrow_up(sh, hist);
	else if (c == ARROW_DOWN)
	{
		if (sh->search == sh->h_num)
			return ;
		process_arrow_down(sh, hist);
	}
}
