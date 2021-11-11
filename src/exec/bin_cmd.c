/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:32:45 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:32:48 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_error_code(void)
{
	if (errno == 2)
		return (127);
	if (errno == 13)
		return (126);
	return (1);
}

t_bool	error_bin_cmd(
	char *error_msg, int exit_code, t_cmd *cmd_list, t_data *data)
{
	display_error_message(
		cmd_list->command, error_msg, cmd_list->error_output);
	close_fd(&cmd_list);
	clean_data(data);
	exit(exit_code);
	return (FAIL);
}

void	update_path(t_cmd **cmd_list, t_data *data)
{
	free_double_str(data->all_paths);
	data->all_paths = get_paths(data);
	(*cmd_list)->path = find_cmd_path(
			(*cmd_list)->command, (*cmd_list)->path, data->all_paths);
}

t_bool	exec_bin_command(pid_t *pid, t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;

	update_path(&cmd_list, data);
	if (cmd_list->input == -1 || cmd_list->output == -1)
		return (FAIL);
	*pid = fork();
	if (*pid < 0)
		return (FAIL);
	if (*pid == CHILD)
	{
		dup2(cmd_list->input, STDIN_FILENO);
		dup2(cmd_list->output, STDOUT_FILENO);
		dup2(cmd_list->error_output, STDERR_FILENO);
		close_all_fd(data);
		cmd_array = fill_cmd_array(cmd_list, data);
		data->envp = env_to_char(data->env);
		if (!cmd_list->path)
			return (error_bin_cmd(
					"No such file or directory", 127, cmd_list, data));
		execve(cmd_list->path, cmd_array, data->envp);
		return (
			error_bin_cmd(strerror(errno), get_error_code(), cmd_list, data));
	}
	return (SUCCESS);
}