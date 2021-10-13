/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:59 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 04:12:00 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_config *sh)
{
	sh->cx = 0;
	sh->cy = 0;
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
	init_shell(sh);
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
