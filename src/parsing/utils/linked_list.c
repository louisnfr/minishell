/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:51:08 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 21:31:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_cmd(t_cmd **cmd_list, t_data *data)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
	{
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(NULL, "malloc()", data);
	}
	setup_cmd_list(new_cmd, data);
	new_cmd->next = NULL;
	while ((*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	(*cmd_list)->next = new_cmd;
	(*cmd_list) = (*cmd_list)->next;
}

void	setup_cmd_list(t_cmd *cmd_list, t_data *data)
{
	cmd_list->command = NULL;
	cmd_list->options = NULL;
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->is_builtin = FALSE;
	cmd_list->delimiter = 0;
	cmd_list->redirection = NULL;
	cmd_list->redir_error = FALSE;
	cmd_list->files = NULL;
	cmd_list->parenthese = OUT;
	cmd_list->par_lvl = data->par_lvl;
	cmd_list->input = 0;
	cmd_list->output = 1;
	cmd_list->error_output = 2;
	cmd_list->pipe_fd = NULL;
	cmd_list->nb_of_pipes = 0;
	cmd_list->heredoc = FALSE;
	cmd_list->heredoc_delimiter = NULL;
	cmd_list->next = NULL;
}
