/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:23 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/25 18:06:51y efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_error(t_cmd **cmd_list)
{
	ft_putstr_fd(NULL, (*cmd_list)->output);
	display_error_message(
		(*cmd_list)->command, "command not found", (*cmd_list)->error_output);
	return (127);
}

/*
t_bool	is_first_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->delimiter != PIPE && cmd_list->next
		&& cmd_list->next->delimiter == PIPE);
}

t_bool	is_last_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->delimiter == PIPE && (!cmd_list->next
 		|| (cmd_list->next && cmd_list->next->delimiter != PIPE)));
}

static int	exec_cmd_in_pipe(t_cmd **cmd_list, t_data *data)
{
	char	**cmd_array;
	int		exit_code;

	if ((*cmd_list)->is_builtin)
		exit_code = exec_builtin(*cmd_list, data);
	else if ((*cmd_list)->path)
	{
		dup2((*cmd_list)->input, STDIN_FILENO);
		dup2((*cmd_list)->output, STDOUT_FILENO);
		dup2((*cmd_list)->error_output, STDERR_FILENO);
		close_all_fd(data);
		cmd_array = fill_cmd_array(*cmd_list, data);
		data->envp = env_to_char(data->env);
		if (!(*cmd_list)->path)
			return (error_exec_cmd("No such file or directory", 127, *cmd_list, data));
		execve((*cmd_list)->path, cmd_array, data->envp);
		return (error_exec_cmd(strerror(errno), get_error_code(), *cmd_list, data));
	}
	else
		exit_code = (handle_error(cmd_list));
	close_fd(cmd_list);
	exit(exit_code);
	return (exit_code);
}

int	create_fork(t_data *data)
{
	data->pipe_pid = fork();
	if (data->pipe_pid == CHILD)
		return (0);
	return (1);
}

void	pipe_recursion(t_cmd **cmd_list, t_data *data)
{
	int	pipe;	
	
	pipe = create_fork(data);
	if (pipe == CHILD && *cmd_list && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
		pipe_recursion(&(*cmd_list)->next, data);
	if (pipe == CHILD)
		exec_cmd_in_pipe(cmd_list, data);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int	exit_code;
	int	status;

	update_path(cmd_list, data);
	pipe_recursion(cmd_list, data);
	close_all_fd(data);
	waitpid(data->pipe_pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	while ((*cmd_list) && ((*cmd_list)->delimiter == PIPE
			|| ((*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)))
		*cmd_list = (*cmd_list)->next;
	return (exit_code);
}
*/

static t_bool	exec_command_pipe(
	int *exit_code, t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**cmd_array;

	if ((*cmd_list)->input == -1 || (*cmd_list)->output == -1)
	{
		*exit_code = 1;
		return (SUCCESS);
	}
	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		dup2((*cmd_list)->input, STDIN_FILENO);
		dup2((*cmd_list)->output, STDOUT_FILENO);
		dup2((*cmd_list)->error_output, STDERR_FILENO);
		close_all_fd(data);
		cmd_array = fill_cmd_array(*cmd_list, data);
		data->envp = env_to_char(data->env);
		if (!(*cmd_list)->path)
			return (error_exec_cmd("No such file or directory", 127, *cmd_list, data));
		execve((*cmd_list)->path, cmd_array, data->envp);
		return (error_exec_cmd(strerror(errno), get_error_code(), *cmd_list, data));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*exit_code = WEXITSTATUS(status);
		return (SUCCESS);
	}
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	update_path(cmd_list, data);
	while ((*cmd_list) && ((*cmd_list)->delimiter == PIPE
			|| ((*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)))
	{
		if ((*cmd_list)->is_builtin)
			exit_code = exec_builtin(*cmd_list, data);
		else if ((*cmd_list)->path)
		{
			if (!exec_command_pipe(&exit_code, cmd_list, data))
				return (FAIL);
		}
		else
			exit_code = (handle_error(cmd_list));
		close_fd(cmd_list);
		*cmd_list = (*cmd_list)->next;
	}
	return (exit_code);
}
