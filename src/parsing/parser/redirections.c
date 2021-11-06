/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/05 16:56:07 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_redir(int fd, char *filename, char *errno_msg)
{
	ft_putstr_fd("bash: ", fd);
	ft_putstr_fd(filename, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(errno_msg, fd);
	ft_putchar_fd('\n', fd);
}

int	open_file(char *file, int flag, t_cmd *cmd_list)
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
			display_error_redir(cmd_list->error_output, file, strerror(errno));
	}
	return (fd);
}

void	handle_redirection(
	int redirection, char **argv, t_cmd *cmd_list, t_data *data)
{
	if (redirection == RIGHT_MARK)
		cmd_list->output = open_file(argv[data->i], WRITE_TRUNC, cmd_list);
	if (redirection == DOUBLE_RIGHT_MARK)
		cmd_list->output = open_file(argv[data->i], WRITE_APPEND, cmd_list);
	if (redirection == LEFT_MARK)
		cmd_list->input = open_file(argv[data->i], READ, cmd_list);
	if (redirection == ERROR)
		cmd_list->error_output = open_file(
				argv[data->i], WRITE_TRUNC, cmd_list);
	if (redirection == DOUBLE_ERROR)
		cmd_list->error_output = open_file(
				argv[data->i], WRITE_APPEND, cmd_list);
	data->i++;
	if (argv[data->i] && str_is_equal(argv[data->i], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		data->i++;
	}
}

void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;

	redirection = 0;
	parse_redirections_heredoc(argv, cmd_list, data);
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		data->i++;
		if (!argv[data->i])
			return ;
		if (redirection != HEREDOC)
			handle_redirection(redirection, argv, cmd_list, data);
		else
			data->i++;
	}
	cmd_list->redirection = redirection;
}
