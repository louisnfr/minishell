/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/05 16:33:19 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fonction(void)
{
	system("leaks minishell");
}

void	clean_data(t_data *data)
{
	clean_cmd_list(data->cmd_list);
	data->cmd_list = NULL;
	free_env(data->env);
	free_double_str(data->all_paths);
}

void	exec_exit(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	// write(1, "exit\n", 6);
	// free_split(cmd);
	// free data
	clean_data(data);
	// atexit(fonction);
	exit(data->ret_value);
}
