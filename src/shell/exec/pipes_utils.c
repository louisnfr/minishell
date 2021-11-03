/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:33 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/03 22:45:44 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error_cmd_pipe(t_cmd **cmd_list)
{
	ft_putstr_fd(NULL, (*cmd_list)->output);
	display_error_message(
		(*cmd_list)->command, "command not found", (*cmd_list)->error_output);
	return (127);
}

t_bool	is_last_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->delimiter == PIPE && (!cmd_list->next
			|| (cmd_list->next && cmd_list->next->delimiter != PIPE)));
}

t_bool	is_first_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->delimiter != PIPE && cmd_list->next
		&& cmd_list->next->delimiter == PIPE);
}

t_bool	create_fork(int i, pid_t *pid)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (-1);
	if (pid[i] == CHILD)
		return (1);
	return (0);
}
