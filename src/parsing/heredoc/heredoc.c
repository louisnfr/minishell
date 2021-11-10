/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:09:07 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/06 10:50:16 by EugenieFran      ###   ########.fr       */
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

t_bool	open_heredoc(int *fd, t_cmd *cmd_list)
{
	*fd = open(cmd_list->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		display_error_message(
			cmd_list->heredoc, strerror(errno), cmd_list->error_output);
		return (FAIL);
	}
	return (SUCCESS);
}

void	write_line(int fd, t_bool quotes, char **line, t_data *data)
{
	if (!quotes)
		*line = parse_heredoc_line(*line, data);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
}

t_bool	read_heredoc(t_bool quotes, t_cmd *cmd_list, t_data *data)
{
	char	*line;
	int		fd;

	if (!open_heredoc(&fd, cmd_list))
		return (FAIL);
	line = NULL;
	while (1)
	{
		line = heredoc_shell(
				data, data->sh, data->sh->history, cmd_list->heredoc_delimiter);
		if (!line)
		{
			if (close(fd) == -1)
				return (FAIL);
			fd = open(cmd_list->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			break ;
		}
		if (line && str_is_equal(line, cmd_list->heredoc_delimiter))
			break ;
		write_line(fd, quotes, &line, data);
		clean_free(&line);
	}
	clean_free(&line);
	return (SUCCESS);
}

char	*heredoc_shell(
	t_data *data, t_config *sh, t_history *hist, char *delimiter)
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