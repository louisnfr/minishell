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

static int	handle_error(t_cmd **cmd_list)
{
	ft_putstr_fd(NULL, (*cmd_list)->output);
	display_error_message(
		(*cmd_list)->command, "command not found", (*cmd_list)->error_output);
	return (127);
}


/*
static int	execute_command(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	char	**cmd_array;
	
	if ((*cmd_list)->is_builtin)
		*exit_code = exec_builtin(*cmd_list, data);
	else if ((*cmd_list)->path)
	{
		cmd_array = fill_cmd_array(*cmd_list, data);
		data->envp = env_to_char(data->env);
		if (!(*cmd_list)->path)
			return (error_exec_cmd("No such file or directory", 127, *cmd_list, data));
		printf("--> cmd = %s | input = %d | output = %d\n", (*cmd_list)->command, (*cmd_list)->input, (*cmd_list)->output);
		execve((*cmd_list)->path, cmd_array, data->envp);
		return (error_exec_cmd(strerror(errno), get_error_code(), *cmd_list, data));
	}
	else
		*exit_code = (handle_error(cmd_list));
	close_fd(cmd_list);
	return (*exit_code);
}


int	fork_pipe(t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == CHILD)
	{
		if ((*cmd_list)->path)
		{
			dup2((*cmd_list)->input, STDIN_FILENO);
			printf("@@@@@@@@@@@@@@@@@@@@\n");
			dup2((*cmd_list)->output, STDOUT_FILENO);
			printf("+++++++++++++++++++\n");
			dup2((*cmd_list)->error_output, STDERR_FILENO);
			close_all_fd(data);
		}
		data->is_parent = 0;
		return (1);
	}
	else
	{
		return (2);
	}
}

int	pipe_recursion(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	int		pipe;
	
	printf("BEGIN\n");
	exit_code = EXIT_SUCCESS;
	pipe = 0;
//	if (*cmd_list && (*cmd_list)->delimiter == PIPE)
	pipe = fork_pipe(cmd_list, data);
	printf("---> is_parent = %d | pipe = %d\n", data->is_parent, pipe);
	if (pipe != 2 && *cmd_list && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
		pipe = pipe_recursion(&(*cmd_list)->next, data);
	if (pipe != 2)
		exit_code = execute_command(&exit_code, cmd_list, data);
	return (exit_code);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int	status;
	int	exit_code;

	data->is_parent = 1;
	update_path(cmd_list, data);
	exit_code = pipe_recursion(cmd_list, data);
	close_all_fd(data);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (!data->is_parent)
		exit(exit_code);
	printf("\nDONE !\n");
	*cmd_list = (*cmd_list)->next;
	return (exit_code);
}

t_bool	fork_pipe(int *pipe_fd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == CHILD)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		if (pipe_fd[1] > 0)
			close(pipe_fd[1]);
		if (pipe_fd[0] > 0)
			close(pipe_fd[0]);
		data->pipe_pid = -1;
		return (1);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (pipe_fd[1] > 0)
			close(pipe_fd[1]);
		if (pipe_fd[0] > 0)
			close(pipe_fd[0]);
		data->pipe_pid = pid;
		return (2);
	}
	return (SUCCESS);
}

int	*create_pipe(t_cmd **cmd_list)
{
	int	*pipe_fd;

	pipe_fd = (int *)ft_calloc(1, sizeof(int) * 2);
	pipe(pipe_fd);
	printf("CREATION pipe_fd[0] = %d | pipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	(*cmd_list)->output = pipe_fd[1];	
	(*cmd_list)->next->input = pipe_fd[0];	
	return (pipe_fd);
}

int	pipes_recursion(t_cmd **cmd_list, int *pipe_fd, t_data *data)
{
	int		exit_code;
	int		pipe;

	exit_code = EXIT_SUCCESS;
	update_path(cmd_list, data);
	pipe = 0;
	if ((*cmd_list) && (*cmd_list)->delimiter == PIPE)
	{
		printf(">>>>>>>>>>> CMD = %s\n", (*cmd_list)->command);
		pipe = fork_pipe(pipe_fd, data);
	}
	if ((*cmd_list) && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE && data->pipe_pid == -1)
	{
		pipe_fd = create_pipe(cmd_list);
		printf("*********** CMD = %s\n", (*cmd_list)->command);
		pipes_recursion(&(*cmd_list)->next, pipe_fd, data);
	}
	if (data->pipe_pid == -1)
	{		
		printf("############# CMD = %s\n", (*cmd_list)->command);
		if ((*cmd_list)->is_builtin)
			exit_code = exec_builtin(*cmd_list, data);
		else if ((*cmd_list)->path)
		{
			if (!exec_command_pipe(&exit_code, cmd_list, data))
				return (FAIL);
		}
		else
			exit_code = (handle_error(cmd_list));
	}
	return (exit_code);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int	exit_code;
	int	status;

	exit_code = pipes_recursion(cmd_list, NULL, data);
	close_fd(cmd_list);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (!data->pipe_pid)
		exit(exit_code);
	*cmd_list = (*cmd_list)->next;
	return (exit_code);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	exit_code = EXIT_SUCCESS;
	update_path(cmd_list, data);
	tmp = *cmd_list;
	if (*cmd_list && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
	{
		*cmd_list = (*cmd_list)->next;
		pid = fork_pipe(&exit_code, &tmp, data);
		printf("--> pid = %d\n", pid);
		if (pid == CHILD)
		{
			printf("hey !\n");
			exec_pipes(cmd_list, data);
			if (tmp && !tmp->is_builtin && !tmp->path)
				exit_code = (handle_error(&tmp));
			else if (tmp && tmp->is_builtin)
				exit_code = exec_builtin(tmp, data);
			else if (tmp && tmp->path)
			{
				exec_command_pipe(&exit_code, &tmp, data);
				close_fd(&tmp);
			}
			exit(exit_code);
		}
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		return (exit_code);	
	}
	printf("****** COMMAND = %s\n", (*cmd_list)->command);
	if (tmp && !tmp->is_builtin && !tmp->path)
		exit_code = (handle_error(&tmp));
	else if (tmp && tmp->is_builtin)
		exit_code = exec_builtin(tmp, data);
	else if (tmp && tmp->path)
	{
		if (!exec_command_pipe(&exit_code, &tmp, data))
			return (FAIL);
	}
	close_fd(&tmp);
	*cmd_list = (*cmd_list)->next;
	return (exit_code);
}
*/

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
