/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:23 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 23:13:55 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	exec_command_pipe(
	int *exit_code, t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**cmd_array;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		if ((*cmd_list)->input == -1 || (*cmd_list)->output == -1)
		{
			*exit_code = 1;
			return (SUCCESS);
		}
		dup2((*cmd_list)->input, STDIN_FILENO);
		dup2((*cmd_list)->output, STDOUT_FILENO);
		dup2((*cmd_list)->error_output, STDERR_FILENO);
		close_all_fd(data);
		cmd_array = fill_cmd_array(*cmd_list, data);
		envp = env_to_char(data->env);
		if (!(*cmd_list)->path)
			return (error_exec_cmd("No such file or directory", 127, *cmd_list, data));
		execve((*cmd_list)->path, cmd_array, envp);
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

static int	handle_error(t_cmd **cmd_list)
{
	ft_putstr_fd(NULL, (*cmd_list)->output);
	display_error_message(
		(*cmd_list)->command, "command not found", (*cmd_list)->error_output);
	return (127);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	(*cmd_list)->path = find_cmd_path((*cmd_list)->command, get_paths(data));
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
