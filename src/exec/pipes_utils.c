/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:53 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/25 14:09:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error_cmd_pipe(t_cmd **cmd_list)
{
	if (!(*cmd_list)->command)
		return (0);
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

void	close_cmd_pipes_fd(t_cmd **cmd_list, t_data *data)
{
	close_all_pipes(cmd_list, data);
	*cmd_list = (*cmd_list)->next;
	while ((*cmd_list) && (*cmd_list)->delimiter == PIPE)
		*cmd_list = (*cmd_list)->next;
}

t_bool	create_fork(int i, pid_t *pid, t_data *data)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (exit_error_bool("fork()", data));
	if (pid[i] == CHILD)
	{
		free(pid);
		return (1);
	}
	return (0);
}
