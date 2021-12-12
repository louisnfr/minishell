/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:23:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/12 17:09:41 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_hist *hist)
{
	t_hist	*tmp;

	if (!hist)
		return ;
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
