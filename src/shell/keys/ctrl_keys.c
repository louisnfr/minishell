/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:13:12 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/15 18:39:49 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	process_ctrl_key(t_data *data, t_config *sh, t_history *hist, int c)
{
	if (c == ctrl_key('d'))
		process_ctrl_d(data, sh);
	else if (c == ctrl_key('c'))
		return (process_ctrl_c(sh));
	else if (c == ctrl_key('l'))
		process_ctrl_l(sh, data);
	else if (c == ctrl_key('u'))
		process_ctrl_u(sh, hist);
	return (SUCCESS);
}

void	process_ctrl_d(t_data *data, t_config *sh)
{
	int	ret;

	ret = data->ret_value;
	if (sh->search == sh->h_num && (!sh->current || !ft_strlen(sh->current)))
	{
		disable_raw_mode(sh);
		printf("exit\n");
		clean_data(data);
		exit(ret);
	}
	else if (sh->search != sh->h_num && (!sh->input || !ft_strlen(sh->input)))
	{
		disable_raw_mode(sh);
		printf("exit\n");
		clean_data(data);
		exit(ret);
	}
}

t_bool	process_ctrl_c(t_config *sh)
{
	free(sh->current);
	free(sh->input);
	write(1, "^C", 2);
	return (FAIL);
}

void	process_ctrl_l(t_config *sh, t_data *data)
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

void	process_ctrl_u(t_config *sh, t_history *hist)
{
	if (sh->search == sh->h_num)
	{
		free(sh->current);
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
