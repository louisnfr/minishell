/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:59 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:31:11 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_values(t_confg *sh)
{
	sh->current = NULL;
	sh->input = NULL;
	sh->prev_cmd = NULL;
	sh->next_cmd = NULL;
	sh->cx = 0;
	sh->cy = 0;
	sh->cx_min = 0;
	sh->cx_max = 0;
	sh->search = sh->h_num;
}

t_confg	*init_config(char **envp)
{
	t_confg	*sh;

	sh = malloc(sizeof(t_confg));
	if (!sh)
		return (NULL);
	sh->history = NULL;
	sh->h_num = 1;
	sh->envp = envp;
	sh->init_termios = FALSE;
	return (sh);
}

t_hist	*init_history(void)
{
	t_hist	*history;

	history = malloc(sizeof(t_hist));
	if (!history)
		return (NULL);
	history = NULL;
	return (history);
}
