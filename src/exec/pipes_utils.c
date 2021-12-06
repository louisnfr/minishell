/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:53 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/06 18:24:02 by efrancon         ###   ########.fr       */
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

void	init_fd(int fd, t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->cmd_list->next;
	while (cmd)
	{
		if (cmd->input == fd)
			cmd->input = 0;
		if (cmd->output == fd)
			cmd->output = 1;
		if (cmd->error_output == fd)
			cmd->error_output = 2;
		cmd = cmd->next;
	}
}

void	close_cmd_pipes_fd(t_cmd **cmd_list, t_data *data)
{
	close_all_pipes(cmd_list, data);
	close_fd(cmd_list, data);
	*cmd_list = (*cmd_list)->next;
	while ((*cmd_list) && (*cmd_list)->delimiter == PIPE)
	{
		close_fd(cmd_list, data);
		*cmd_list = (*cmd_list)->next;
	}
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
