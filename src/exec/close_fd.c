/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:19 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:36:22 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		close((*cmd)->pipe_fd[i][0]);
		close((*cmd)->pipe_fd[i][1]);
	}
}

void	close_other_pipes(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input != (*cmd)->pipe_fd[i][0])
			close((*cmd)->pipe_fd[i][0]);
		if ((*cmd)->output != (*cmd)->pipe_fd[i][1])
			close((*cmd)->pipe_fd[i][1]);
	}
}

void	close_pipe(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (++i < (*cmd)->nb_of_pipes)
	{
		if ((*cmd)->input == (*cmd)->pipe_fd[i][0])
			close((*cmd)->pipe_fd[i][0]);
		if ((*cmd)->output == (*cmd)->pipe_fd[i][1])
			close((*cmd)->pipe_fd[i][1]);
	}	
}

void	close_all_fd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list->next;
	while (cmd)
	{
		if (cmd->input > 2)
			close(cmd->input);
		if (cmd->output > 2)
			close(cmd->output);
		if (cmd->error_output > 2)
			close(cmd->error_output);
		cmd = cmd->next;
	}
}

void	close_fd(t_cmd **cmd_list)
{
	if (!cmd_list || !*cmd_list)
		return ;
	if ((*cmd_list)->input > 2)
		close((*cmd_list)->input);
	if ((*cmd_list)->output > 2)
		close((*cmd_list)->output);
	if ((*cmd_list)->error_output > 2)
		close((*cmd_list)->error_output);
}
