/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 05:59:40 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_history(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	print_history(data->sh->history);
	return (EXIT_SUCCESS);
}
