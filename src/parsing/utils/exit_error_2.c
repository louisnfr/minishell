/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:28:17 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:29:29 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_home(
	char *pid_value, char *ret_value, t_cmd *cmd_list, t_data *data)
{
	clean_free(&pid_value);
	clean_free(&ret_value);
	if (cmd_list->path)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit_error_child(NULL, NULL, "malloc()", data);
	}
	exit_error_str(NULL, "malloc()", data);
}

void	exit_error_args(
	int nb_of_args, char **args, t_cmd *cmd_list, t_data *data)
{
	free_args(nb_of_args, args);
	if (cmd_list->path)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit_error_child(NULL, NULL, "malloc()", data);
	}
	exit_error_str(NULL, "malloc()", data);
}
