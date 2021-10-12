#include "minishell.h"

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
		if (str_is_equal(line, cmd_list->delimiter))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		clean_free(&line);
	}
	clean_free(&line);
	if (close(fd) == -1)
		exit_error_with_msg("close() failed: ", strerror(errno), data);
	return (SUCCESS);
}
