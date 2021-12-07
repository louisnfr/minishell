/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:28:32 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/07 15:08:36 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_env(t_cmd *cmd_list, t_data *data)
{
	if (cmd_list->args)
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(cmd_list->args[0], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		return (127);
	}
	print_env(data->env, cmd_list);
	return (EXIT_SUCCESS);
}
