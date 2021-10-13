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

t_bool	read_heredoc(t_cmd *cmd_list, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(cmd_list->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (FAIL);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(0, &line);
		if (str_is_equal(line, cmd_list->heredoc_delimiter))
			break ;
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
