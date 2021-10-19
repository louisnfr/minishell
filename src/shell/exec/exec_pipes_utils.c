/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:33 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/17 12:35:35 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
