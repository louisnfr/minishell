/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:19 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 19:50:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_cmd **cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		safe_close_fd((*cmd)->pipe_fd[i][0], data);
		(*cmd)->pipe_fd[i][0] = 0;
		safe_close_fd((*cmd)->pipe_fd[i][1], data);
		(*cmd)->pipe_fd[i][1] = 0;
	}
}

void	close_other_pipes(t_cmd **cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input != (*cmd)->pipe_fd[i][0])
		{
			safe_close_fd((*cmd)->pipe_fd[i][0], data);
			(*cmd)->pipe_fd[i][0] = 0;
		}
		if ((*cmd)->output != (*cmd)->pipe_fd[i][1])
		{
			safe_close_fd((*cmd)->pipe_fd[i][1], data);
			(*cmd)->pipe_fd[i][1] = 0;
		}
	}
}

void	close_pipe(t_cmd **cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input == (*cmd)->pipe_fd[i][0])
		{
			safe_close_fd((*cmd)->pipe_fd[i][0], data);
			(*cmd)->pipe_fd[i][0] = 0;
		}
		if ((*cmd)->output == (*cmd)->pipe_fd[i][1])
		{
			safe_close_fd((*cmd)->pipe_fd[i][1], data);
			(*cmd)->pipe_fd[i][1] = 0;
		}
	}	
}

void	close_all_fd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list->next;
	while (cmd)
	{
		safe_close_fd(cmd->input, data);
		safe_close_fd(cmd->output, data);
		safe_close_fd(cmd->error_output, data);
		cmd = cmd->next;
	}
}

void	close_fd(t_cmd **cmd_list, t_data *data)
{
	if (!cmd_list || !*cmd_list)
		return ;
	if ((*cmd_list)->input > 2)
		safe_close_fd((*cmd_list)->input, data);
	if ((*cmd_list)->output > 2)
		safe_close_fd((*cmd_list)->output, data);
	if ((*cmd_list)->error_output > 2)
		safe_close_fd((*cmd_list)->error_output, data);
}
