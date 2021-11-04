/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:51:08 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:57:05 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (FAIL);
	setup_cmd_list(new_cmd);
	if (cmd)
	{
		new_cmd->command = ft_strdup(cmd);
		clean_free(&cmd);
	}
	new_cmd->options = options;
	if (path)
	{
		new_cmd->path = ft_strdup(path);
		clean_free(&path);
	}
	new_cmd->next = NULL;
	while ((*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	(*cmd_list)->next = new_cmd;
	(*cmd_list) = (*cmd_list)->next;
	return (SUCCESS);
}

void	setup_cmd_list(t_cmd *cmd_list)
{
	cmd_list->command = NULL;
	cmd_list->options = NULL;
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->is_builtin = FALSE;
	cmd_list->delimiter = 0;
	cmd_list->redirection = 0;
	cmd_list->parenthese = OUT;
	cmd_list->input = 0;
	cmd_list->output = 1;
	cmd_list->error_output = 2;
	cmd_list->pipe_fd = NULL;
	cmd_list->nb_of_pipes = 0;
	cmd_list->heredoc = NULL;
	cmd_list->heredoc_delimiter = NULL;
	cmd_list->next = NULL;
}
