/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/18 17:49:01 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_list(t_cmd *cmd_list, t_data *data)
{
	(void)data;
	if (!cmd_list)
		return ;
	cmd_list->is_builtin = 0;
	cmd_list->delimiter = 0;
	cmd_list->input = 0;
	cmd_list->output = 1;
	cmd_list->error_output = 2;
	clean_free(&cmd_list->command);
	if (cmd_list->options)
		free_double_str(cmd_list->options);
	if (cmd_list->args)
		free_double_str(cmd_list->args);
	clean_free(&cmd_list->path);
	if (cmd_list->heredoc)
	{
		clean_free(&cmd_list->heredoc);
		clean_free(&cmd_list->heredoc_delimiter);
	}
	if (cmd_list->pipe_fd)
		free_fd_array(cmd_list->nb_of_pipes, cmd_list->pipe_fd);
	free(cmd_list);
	cmd_list = NULL;
}

void	clean_cmd_list(t_cmd **cmd_list, t_data *data)
{
	t_cmd	*tmp;

	if (!(*cmd_list) || !cmd_list)
		return ;
	tmp = *cmd_list;
	*cmd_list = (*cmd_list)->next;
	remove_from_list(tmp, data);
	tmp = *cmd_list;
	while (tmp)
	{
		*cmd_list = (*cmd_list)->next;
		remove_from_list(tmp, data);
		tmp = *cmd_list;
	}
	free(*cmd_list);
	(*cmd_list) = NULL;
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	data->i = 0;
	data->pid = 0;
	data->ret_value = 0;
	clean_cmd_list(&data->cmd_list, data);
	free_double_str(data->all_paths);
	free_double_str(data->envp);
	free_double_str(data->builtins);
	clean_free(&data->last_cwd);
	free_env(data->env);
	free_env(data->export);
	clean_free(&data->prpt);
	free_history(data->sh->history);
	free(data->sh);
	free(data);
	data = NULL;
}
