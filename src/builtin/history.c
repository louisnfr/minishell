/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 20:45:03 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(t_history *hist)
{
	int	i;

	i = 1;
	hist = getlast(hist);
	while (hist)
	{
		printf("%5d  %s\n", i, hist->cmd);
		hist = hist->previous;
		i++;
	}
}

t_bool	exec_history(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	print_history(data->sh->history);
	return (EXIT_SUCCESS);
}
