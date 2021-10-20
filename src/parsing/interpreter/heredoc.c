/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:09:07 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/20 17:23:09 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_heredoc_line(char *line, t_data *data)
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
	pid_value = ft_itoa(data->pid);
	new_line = heredoc_special_value(new_line, pid_value, '$');
	clean_free(&pid_value);
	if (!ft_strchr(new_line, '?'))
		return (new_line);
	ret_value = ft_itoa(data->ret_value);
	new_line = heredoc_special_value(new_line, ret_value, '?');
	clean_free(&ret_value);
	return (new_line);
}

t_bool	read_heredoc(t_cmd *cmd_list, t_data *data, t_bool quotes)
{
	char	*line;
	int		fd;

	fd = open(cmd_list->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		display_error_message(cmd_list->heredoc, strerror(errno), cmd_list->error_output);
		return (FAIL);
	}
	line = NULL;
	while (1)
	{
		line = heredoc_shell(data, data->sh, data->sh->history, cmd_list->heredoc_delimiter);
		if (!line)
			return (FAIL);
		if (line && str_is_equal(line, cmd_list->heredoc_delimiter))
			break ;
		if (!quotes)
			line = parse_heredoc_line(line, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		clean_free(&line);
	}
	clean_free(&line);
	if (close(fd) == -1)
		return (FAIL);
	return (SUCCESS);
}

char	*heredoc_shell(t_data *data, t_config *sh, t_history *hist, char *delimiter)
{
	char	*line;

	line = NULL;
	enable_heredoc_raw_mode(data->sh);
	write(1, "> ", 2);
	line = heredoc_process_keypress(data, sh, hist, delimiter);
	write(1, "\n", 1);
	disable_raw_mode(data->sh);
	return (line);
}
