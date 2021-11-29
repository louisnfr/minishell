/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:03:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:31:11 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(int c)
{
	return (c == ' ' || c == '/' || c == ';' || c == '"');
}

char	*selected_input(t_confg *sh)
{
	if (sh->h_num == sh->search)
		return (sh->current);
	else
		return (sh->input);
}

int	ctrl_key(int k)
{
	return (k & 0x1f);
}

void	clear_prompt(int cx, int k)
{
	int	i;

	i = -1;
	(void)k;
	while (++i < cx)
		write(1, "\x1b[1D", 4);
	write(1, "\x1b[0K", 4);
}
