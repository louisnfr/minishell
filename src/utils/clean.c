/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/02 16:57:11 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_list(t_cmd *cmd_list)
{
	if (!cmd_list)
		return ;
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
	remove_from_list(tmp);
	tmp = *cmd_list;
	while (tmp)
	{
		*cmd_list = (*cmd_list)->next;
		remove_from_list(tmp);
		tmp = *cmd_list;
	}
	free(*cmd_list);
	(*cmd_list) = NULL;
	close_all_fd(data);
	// clean_free(&data->sh->current);
	clean_free(&data->sh->input);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	data->i = 0;
	data->pid = 0;
	data->ret_value = 0;
	data->par_lvl = 0;
	clean_cmd_list(&data->cmd_list, data);
	free_double_str(data->all_paths);
	if (data->envp)
		free_double_str(data->envp);
	free_double_str(data->builtins);
	clean_free(&data->last_cwd);
	clean_free(&data->prpt);
	free_history(data->sh->history);
	free_env(data->env);
	free_env(data->export);
	free(data->sh);
	free(data);
	data = NULL;
}
