/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:28:32 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 18:47:20 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_env(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	print_env(data->env);
	return (EXIT_SUCCESS);
}
