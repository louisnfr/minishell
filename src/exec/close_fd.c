/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:19 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:40:29 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_cmd **cmd, pid_t *pid, t_data *data)
{
	int	i;

	i = -1;
	while ((*cmd)->nb_of_pipes && ++i < (*cmd)->nb_of_pipes)
	{
		safe_close_fd((*cmd)->pipe_fd[i][0], pid, data);
		init_fd((*cmd)->pipe_fd[i][0], &data);
		(*cmd)->pipe_fd[i][0] = 0;
		safe_close_fd((*cmd)->pipe_fd[i][1], pid, data);
		init_fd((*cmd)->pipe_fd[i][1], &data);
		(*cmd)->pipe_fd[i][1] = 1;
	}
}

void	close_other_pipes(t_cmd **cmd, pid_t *pid, t_data *data)
{
	int	i;

	i = -1;
	while ((*cmd)->nb_of_pipes && ++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input != (*cmd)->pipe_fd[i][0])
		{
			safe_close_fd((*cmd)->pipe_fd[i][0], pid, data);
			(*cmd)->pipe_fd[i][0] = 0;
		}
		if ((*cmd)->output != (*cmd)->pipe_fd[i][1])
		{
			safe_close_fd((*cmd)->pipe_fd[i][1], pid, data);
			(*cmd)->pipe_fd[i][1] = 1;
		}
	}
}

void	close_pipe(t_cmd **cmd, pid_t *pid, t_data *data)
{
	int	i;

	i = -1;
	while ((*cmd)->nb_of_pipes && ++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input == (*cmd)->pipe_fd[i][0])
		{
			safe_close_fd((*cmd)->pipe_fd[i][0], pid, data);
			(*cmd)->pipe_fd[i][0] = 0;
		}
		if ((*cmd)->output == (*cmd)->pipe_fd[i][1])
		{
			safe_close_fd((*cmd)->pipe_fd[i][1], pid, data);
			(*cmd)->pipe_fd[i][1] = 1;
		}
	}	
}

void	close_fd(t_cmd **cmd_list, pid_t *pid, t_data *data)
{
	if (!cmd_list || !*cmd_list)
		return ;
	if ((*cmd_list)->input > 2)
	{
		safe_close_fd((*cmd_list)->input, pid, data);
		(*cmd_list)->input = 0;
	}
	if ((*cmd_list)->output > 2)
	{
		safe_close_fd((*cmd_list)->output, pid, data);
		(*cmd_list)->output = 1;
	}
	if ((*cmd_list)->error_output > 2)
	{
		if (!(*cmd_list)->redir_error)
			safe_close_fd((*cmd_list)->error_output, pid, data);
		(*cmd_list)->error_output = 2;
	}
}

void	close_all_fd(pid_t *pid, t_data *data)
{
	t_cmd	*cmd;

	if (data && data->cmd_list)
	{
		cmd = data->cmd_list->next;
		while (cmd)
		{
			close_fd(&cmd, pid, data);
			cmd = cmd->next;
		}
	}
}
