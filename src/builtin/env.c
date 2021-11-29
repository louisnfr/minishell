/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:28:32 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 18:55:01 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_env(t_cmd *cmd_list, t_data *data)
{
	if (cmd_list->args)
		return (EXIT_FAILURE);
	print_env(data->env, cmd_list);
	return (EXIT_SUCCESS);
}
