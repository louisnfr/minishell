/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:17:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/02 11:03:03 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error_msg_exec(int *exit_code, char *command, int fd_error)
{
	if (!command)
	{
		*exit_code = 0;
		return ;
	}
	*exit_code = 127;
	if (command && ft_strchr(command, '/'))
		display_error_message(
			command, "No such file or directory", fd_error);
	else if (command)
		display_error_message(command, "command not found", fd_error);
}

t_bool	init_exec(
	int *exit_code, int *error_file, t_cmd **cmd_list, t_data *data)
{
	*error_file = FALSE;
	*exit_code = EXIT_FAILURE;
	if (!data->cmd_list->next)
	{
		data->ret_value = *exit_code;
		return (0);
	}	
	*cmd_list = data->cmd_list->next;
	return (1);
}
