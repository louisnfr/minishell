/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:23:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/06 23:43:28 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_hist *hist)
{
	t_hist	*tmp;

	tmp = hist;
	while (tmp)
	{
		hist = hist->next;
		clean_free(&tmp->cmd);
		clean_free(&tmp->new);
		free(tmp);
		tmp = NULL;
		tmp = hist;
	}
	free(tmp);
	free(hist);
	hist = NULL;
}
