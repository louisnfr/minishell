/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:26:09 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 21:13:59 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_arrow_key(t_config *sh, t_history *hist, int c)
{
	if (c == ARROW_LEFT)
		move_cursor_left(sh);
	else if (c == ARROW_RIGHT)
		move_cursor_right(sh);
	else if (c == ARROW_UP)
		process_arrow_up(sh, hist);
	else if (c == ARROW_DOWN)
		process_arrow_down(sh, hist);
}

void	move_cursor_left(t_config *sh)
{
	if (sh->cx > sh->cx_min)
	{
		write(1, "\x1b[1D", 4);
		sh->cx--;
	}
}

void	move_cursor_right(t_config *sh)
{
	if (sh->cx < sh->cx_max)
	{
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
}

void	process_arrow_up(t_config *sh, t_history *hist)
{
	sh->prev_cmd = find_cmd_history(hist, sh->search - 1);
	if (sh->prev_cmd)
	{
		sh->search--;
		if (sh->input)
			free(sh->input);
		sh->input = malloc(sizeof(char) * (ft_strlen(sh->prev_cmd) + 1));
		ft_strcpy(sh->input, sh->prev_cmd);
		clear_prompt(sh->cx, ft_strlen(sh->prev_cmd));
		write(1, sh->input, ft_strlen(sh->input));
		sh->cx = ft_strlen(sh->input);
		sh->cx_max = ft_strlen(sh->input);
	}
}

void	process_arrow_down(t_config *sh, t_history *hist)
{
	if (sh->search == sh->h_num)
		return ;
	sh->next_cmd = find_cmd_history(hist, sh->search + 1);
	clear_prompt(sh->cx, ft_strlen(sh->next_cmd));
	if (sh->next_cmd)
	{
		if (sh->input)
			free(sh->input);
		sh->input = malloc(sizeof(char) * (ft_strlen(sh->next_cmd) + 1));
		ft_strcpy(sh->input, sh->next_cmd);
		write(1, sh->input, ft_strlen(sh->input));
		sh->cx = ft_strlen(sh->input);
		sh->cx_max = ft_strlen(sh->input);
	}
	else if (!sh->next_cmd)
	{
		free(sh->input);
		sh->input = NULL;
		if (sh->current)
			write(1, sh->current, ft_strlen(sh->current));
		sh->cx = ft_strlen(sh->current);
		sh->cx_max = ft_strlen(sh->current);
	}
	sh->search++;
}
