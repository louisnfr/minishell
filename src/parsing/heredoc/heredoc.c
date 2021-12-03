/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:09:07 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/03 18:32:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_heredoc_line(char *line, t_data *data)
{
	char	*new_line;
	char	*pid_value;
	char	*ret_value;

	if (!line || !ft_strchr(line, '$'))
		return (line);
	new_line = NULL;
	new_line = heredoc_env_variable(line, data);
	if (!ft_strchr(new_line, '$'))
		return (new_line);
	pid_value = safe_itoa(data->pid, data);
	new_line = heredoc_special_value(new_line, pid_value, '$', data);
	clean_free(&pid_value);
	if (!ft_strchr(new_line, '?'))
		return (new_line);
	ret_value = safe_itoa(data->ret_value, data);
	new_line = heredoc_special_value(new_line, ret_value, '?', data);
	clean_free(&ret_value);
	return (new_line);
}

static void	write_line(int fd, t_bool quotes, char **line, t_data *data)
{
	if (!quotes)
		*line = parse_heredoc_line(*line, data);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	clean_free(line);
}

t_bool	read_heredoc(t_bool quotes, t_cmd **cmd_list, t_data *data)
{
	char	*line;

	if (!data->pipe_heredoc)
	{
		data->pipe_heredoc = (int *)ft_calloc(1, sizeof(int) * 2);
		if (!data->pipe_heredoc || pipe(data->pipe_heredoc) == -1)
			return (exit_error_bool("malloc()", data));
	}
	line = NULL;
	// printf("DELIMITER = %s\n", (*cmd_list)->heredoc_delimiter);
	while (1)
	{
		clean_free(&data->sh->current);
		clean_free(&data->sh->input);
		line = heredoc_shell(data, data->sh, data->sh->history,
				(*cmd_list)->heredoc_delimiter);
		if (!line)
		{
			safe_close_fd(data->pipe_heredoc[1], data);
			safe_close_fd(data->pipe_heredoc[0], data);
			free(data->pipe_heredoc);
			data->pipe_heredoc = (int *)ft_calloc(1, sizeof(int) * 2);
			if (!data->pipe_heredoc || pipe(data->pipe_heredoc) == -1)
				return (exit_error_bool("malloc()", data));
			break ;
		}
		if (line && str_is_equal(line, (*cmd_list)->heredoc_delimiter))
			break ;
		write_line(data->pipe_heredoc[1], quotes, &line, data);
	}
	clean_free(&line);
	(*cmd_list)->input = data->pipe_heredoc[0];
	clean_free(&(*cmd_list)->heredoc_delimiter);
	return (SUCCESS);
}

char	*heredoc_shell(
	t_data *data, t_confg *sh, t_hist *hist, char *delimiter)
{
	char	*line;

	line = NULL;
	enable_heredoc_raw_mode(data->sh);
	write(1, "> ", 2);
	line = heredoc_process_keypress(data, sh, hist, delimiter);
	write(1, "\n", 1);
	disable_raw_mode(data->sh);
	return (safe_strdup(line, data));
}
