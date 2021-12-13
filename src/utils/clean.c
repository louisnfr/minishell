/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:36:30 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_list(t_cmd *cmd_list, t_data *data)
{
	(void)data;
	if (!cmd_list)
		return ;
	if (cmd_list->pipe_fd)
		free_fd_array(cmd_list->nb_of_pipes, cmd_list->pipe_fd);
	clean_free(&cmd_list->command);
	free_double_str(cmd_list->files);
	if (cmd_list->redirection)
	{
		free(cmd_list->redirection);
		cmd_list->redirection = NULL;
	}
	free_double_str(cmd_list->options);
	free_double_str(cmd_list->args);
	clean_free(&cmd_list->path);
	clean_free(&cmd_list->heredoc_delimiter);
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
	close_all_fd(NULL, data);
	clean_free(&data->sh->current);
	clean_free(&data->sh->input);
	if (data->to_suppress)
		clean_free(&data->to_suppress);
}

void	free_pipe_heredoc(t_data *data)
{
	if (data->pipe_heredoc)
	{
		safe_close_fd(data->pipe_heredoc[0], NULL, data);
		safe_close_fd(data->pipe_heredoc[1], NULL, data);
		free(data->pipe_heredoc);
		data->pipe_heredoc = NULL;
	}
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	data->i = 0;
	data->pid = 0;
	data->ret_value = 0;
	data->par_lvl = 0;
	clean_redir(data);
	free_pipe_heredoc(data);
	clean_cmd_list(&data->cmd_list, data);
	free_double_str(data->all_paths);
	if (data->envp)
		free_double_str(data->envp);
	free_double_str(data->builtins);
	clean_free(&data->last_cwd);
	clean_free(&data->prpt);
	if (data->sh && data->sh->history)
		free_history(data->sh->history);
	free_env(data->env);
	free_env(data->export);
	free(data->sh);
	free(data);
	data = NULL;
}
