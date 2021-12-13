/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:32:45 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:34:25 by efrancon         ###   ########.fr       */
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
	char *error_msg, int exit_code, t_cmd **cmd_list, t_data *data)
{
	display_error_message(
		(*cmd_list)->command, error_msg, (*cmd_list)->error_output);
	clean_data(data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(exit_code);
	return (FAIL);
}

t_bool	update_path(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (!(*cmd_list)->path)
		return (SUCCESS);
	free_double_str(data->all_paths);
	data->all_paths = get_paths(data);
	(*cmd_list)->path = find_cmd_path(
			(*cmd_list)->command, (*cmd_list)->path, data->all_paths, data);
	if (!(*cmd_list)->path)
	{
		display_error_message((*cmd_list)->command,
			"No such file or directory", (*cmd_list)->error_output);
		close_fd(cmd_list, NULL, data);
		*exit_code = 127;
		return (FAIL);
	}
	return (SUCCESS);
}

static t_bool	exec_bin_command(pid_t *pid, t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;

	if (cmd_list->input == -1 || cmd_list->output == -1)
		return (FAIL);
	*pid = fork();
	if (*pid < 0)
		exit_error_str(NULL, "fork()", data);
	if (*pid == CHILD)
	{
		dup2(cmd_list->input, STDIN_FILENO);
		dup2(cmd_list->output, STDOUT_FILENO);
		dup2(cmd_list->error_output, STDERR_FILENO);
		close_all_fd(NULL, data);
		cmd_array = fill_cmd_array(cmd_list, data);
		data->envp = env_to_char(data->env, data, cmd_array);
		execve(cmd_list->path, cmd_array, data->envp);
		free_double_str(cmd_array);
		return (
			error_bin_cmd(strerror(errno), get_error_code(), &cmd_list, data));
	}
	return (SUCCESS);
}

void	handle_bin_command(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	int		status;
	pid_t	pid;

	if (!update_path(exit_code, cmd_list, data))
		return ;
	status = 0;
	if (exec_bin_command(&pid, *cmd_list, data))
	{
		ignore_signals();
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			handle_status(WTERMSIG(status), exit_code);
		if (WIFEXITED(status))
			*exit_code = WEXITSTATUS(status);
		recover_signals();
		if (*exit_code == 42)
			exit_error_str(NULL, "child", data);
	}
	close_fd(cmd_list, NULL, data);
}
