/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:59 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 20:33:55 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_values(t_config *sh)
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

t_config	*init_config(char **envp)
{
	t_config	*sh;

	sh = malloc(sizeof(t_config));
	if (!sh)
		return (NULL);
	sh->history = NULL;
	sh->h_num = 1;
	sh->envp = envp;
	sh->init_termios = FALSE;
	return (sh);
}

t_history	*init_history(void)
{
	t_history	*history;

	history = malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history = NULL;
	return (history);
}
