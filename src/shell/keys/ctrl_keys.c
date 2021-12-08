/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:13:12 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/08 22:56:38 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_ctrl_d(t_data *data, t_confg *sh)
{
	int	ret;

	ret = data->ret_value;
	if (sh->search == sh->h_num && (!sh->current || !ft_strlen(sh->current)))
	{
		disable_raw_mode(sh);
		write(2, "exit\n", 5);
		clean_free(&sh->current);
		sh->current = NULL;
		clean_data(data);
		exit(ret);
	}
	else if (sh->search != sh->h_num && (!sh->input || !ft_strlen(sh->input)))
	{
		disable_raw_mode(sh);
		write(2, "exit\n", 5);
		clean_free(&sh->input);
		sh->input = NULL;
		clean_data(data);
		exit(ret);
	}
}

static t_bool	process_ctrl_c(t_data *data, t_confg *sh)
{
	clean_free(&sh->current);
	sh->current = NULL;
	clean_free(&sh->input);
	sh->input = NULL;
	write(1, "^C", 2);
	data->ret_value = 130;
	return (FAIL);
}

static void	process_ctrl_l(t_data *data, t_confg *sh)
{
	write(1, "\x1b[2J", 4);
	write(1, "\x1b[H", 3);
	write(1, "\x1b[999A", 6);
	write(1, "\x1b[999D", 6);
	write(1, data->prpt, ft_strlen(data->prpt));
	if (sh->current && sh->search == sh->h_num)
		write(1, sh->current, ft_strlen(sh->current));
	else
		write(1, sh->input, ft_strlen(sh->input));
}

void	process_ctrl_u(t_confg *sh, t_hist *hist)
{
	if (sh->search == sh->h_num)
	{
		clean_free(&sh->current);
		sh->current = NULL;
		clear_prompt(sh->cx, 1);
		sh->cx = 0;
		sh->cx_max = 0;
	}
	else
	{
		erase_cmd_history(sh->input, sh->history, sh->search);
		sh->input = ft_realloc(sh->input, sizeof(char)
				* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
		ft_strcpy(sh->input, find_cmd_history(hist, sh->search));
		clear_prompt(sh->cx, 1);
		sh->cx = 0;
		sh->cx_max = 0;
	}
}

t_bool	process_ctrl_key(t_data *data, t_confg *sh, t_hist *hist, int c)
{
	if (c == ctrl_key('d'))
		process_ctrl_d(data, sh);
	else if (c == ctrl_key('c'))
		return (process_ctrl_c(data, sh));
	else if (c == ctrl_key('l'))
		process_ctrl_l(data, sh);
	else if (c == ctrl_key('u'))
		process_ctrl_u(sh, hist);
	return (SUCCESS);
}
