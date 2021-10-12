/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:33 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/12 15:16:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_with_msg(char *error_msg, char *errno_msg, t_data *data)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	if (errno_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errno_msg, 2);
	}
	ft_putchar_fd('\n', 2);
	exec_exit(data->cmd_list, data);
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
		cmd = cmd->next;
	}
}

void	close_fd(t_cmd **cmd_list)
{
	if ((*cmd_list)->input > 2)
		close((*cmd_list)->input);
	if ((*cmd_list)->output > 2)
		close((*cmd_list)->output);
}
