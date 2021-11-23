/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:51:25 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/23 14:52:42 by efrancon         ###   ########.fr       */
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

void	open_files(t_cmd *cmd_list)
{
	int	i;

	if (!cmd_list->files || !cmd_list->redirection)
		return ;
	i = -1;
	while (cmd_list->files[++i])
	{
		if (cmd_list->redirection[i] == RIGHT_MARK)
			cmd_list->output = open_file(
					cmd_list->files[i], WRITE_TRUNC, cmd_list);
		else if (cmd_list->redirection[i] == DOUBLE_RIGHT_MARK)
			cmd_list->output = open_file(
					cmd_list->files[i], WRITE_APPEND, cmd_list);
		else if (cmd_list->redirection[i] == LEFT_MARK)
			cmd_list->input = open_file(cmd_list->files[i], READ, cmd_list);
		else if (cmd_list->redirection[i] == ERROR)
			cmd_list->error_output = open_file(
					cmd_list->files[i], WRITE_TRUNC, cmd_list);
		else if (cmd_list->redirection[i] == DOUBLE_ERROR)
			cmd_list->error_output = open_file(
					cmd_list->files[i], WRITE_APPEND, cmd_list);
		if (cmd_list->redir_error)
			cmd_list->error_output = cmd_list->output;
	}
}
