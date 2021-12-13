/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:51:25 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:45:40 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_a_file(t_bool *error, char *file, int flag, t_cmd *cmd_list)
{
	int	fd;

	fd = -1;
	if (file)
	{
		if (flag == WRITE_TRUNC)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (flag == WRITE_APPEND)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (flag == READ)
			fd = open(file, O_RDONLY, 0644);
		if (fd == -1)
		{
			display_error_redir(cmd_list->error_output, file, strerror(errno));
			*error = TRUE;
		}
	}
	return (fd);
}

static void	handle_opening_error_redir(
	int i, int *error, t_cmd **cmd_list, t_data *data)
{
	if ((*cmd_list)->redirection[i] == ERROR)
	{
		safe_close_fd((*cmd_list)->error_output, NULL, data);
		(*cmd_list)->error_output = open_a_file(
				error, (*cmd_list)->files[i], WRITE_TRUNC, *cmd_list);
	}
	else if ((*cmd_list)->redirection[i] == DOUBLE_ERROR)
	{
		safe_close_fd((*cmd_list)->error_output, NULL, data);
		(*cmd_list)->error_output = open_a_file(
				error, (*cmd_list)->files[i], WRITE_APPEND, *cmd_list);
	}
}

static void	handle_opening(int i, int *error, t_cmd **cmd_list, t_data *data)
{
	if ((*cmd_list)->redirection[i] == AMBIGUOUS_REDIR)
		return (handle_ambiguous_redir(error, i, *cmd_list));
	if ((*cmd_list)->redirection[i] == RIGHT_MARK)
	{
		safe_close_fd((*cmd_list)->output, NULL, data);
		(*cmd_list)->output = open_a_file(
				error, (*cmd_list)->files[i], WRITE_TRUNC, *cmd_list);
	}
	else if ((*cmd_list)->redirection[i] == DOUBLE_RIGHT_MARK)
	{
		safe_close_fd((*cmd_list)->output, NULL, data);
		(*cmd_list)->output = open_a_file(
				error, (*cmd_list)->files[i], WRITE_APPEND, *cmd_list);
	}
	else if ((*cmd_list)->redirection[i] == LEFT_MARK)
	{
		safe_close_fd((*cmd_list)->input, NULL, data);
		(*cmd_list)->input = open_a_file(
				error, (*cmd_list)->files[i], READ, *cmd_list);
	}
	else
		handle_opening_error_redir(i, error, cmd_list, data);
	if ((*cmd_list)->redir_error)
		(*cmd_list)->error_output = (*cmd_list)->output;
}

static void	transform_filename(int i, t_cmd *cmd_list, t_data *data)
{
	char	*tmp;

	tmp = safe_strdup(cmd_list->files[i], data);
	cmd_list->files[i] = transform_str(cmd_list->files[i], cmd_list, data);
	if (!cmd_list->files[i] || str_is_equal(cmd_list->files[i], "*"))
	{
		if (!cmd_list->files[i])
			cmd_list->files[i] = safe_strdup(tmp, data);
		cmd_list->redirection[i] = AMBIGUOUS_REDIR;
	}
	clean_free(&tmp);
}

t_bool	open_files(int *exit_code, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_bool	error;

	if (!cmd_list || !cmd_list->files || !cmd_list->redirection)
		return (FALSE);
	i = -1;
	while (cmd_list->files[++i])
	{
		error = FALSE;
		transform_filename(i, cmd_list, data);
		handle_opening(i, &error, &cmd_list, data);
		if (error)
		{
			*exit_code = EXIT_FAILURE;
			data->ret_value = EXIT_FAILURE;
			return (TRUE);
		}
	}
	*exit_code = EXIT_SUCCESS;
	return (FALSE);
}
