/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/02 23:58:56 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_history(t_cmd *cmd_list, t_hist *hist)
{
	int	i;

	i = 1;
	hist = getlast(hist);
	while (hist)
	{
		ft_putnbr_fd(i, cmd_list->output);
		ft_putstr_fd(" ", cmd_list->output);
		ft_putstr_fd(hist->cmd, cmd_list->output);
		ft_putstr_fd("\n", cmd_list->output);
		hist = hist->previous;
		i++;
	}
}

t_bool	exec_history(t_cmd *cmd_list, t_data *data)
{
	print_history(cmd_list, data->sh->history);
	return (EXIT_SUCCESS);
}
