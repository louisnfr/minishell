/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:49:12 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/08 11:49:14 by efrancon         ###   ########.fr       */
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

void	handle_ambiguous_redir(int *error, int i, t_cmd *cmd_list)
{
	ft_putstr_fd("bash: ", cmd_list->error_output);
	ft_putstr_fd(cmd_list->files[i], cmd_list->error_output);
	ft_putstr_fd(": ambiguous redirect\n", cmd_list->error_output);
	*error = TRUE;
}
