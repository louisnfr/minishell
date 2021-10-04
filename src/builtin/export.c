/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/04 17:10:26 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	add_var(&data->env, new_var(cmd->, var[1]));
	return (EXIT_SUCCESS);
}
