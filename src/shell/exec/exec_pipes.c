/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:16:23 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/12 15:16:27 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	exec_command_pipe(
	int *exit_code, char **envp, t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**cmd_array;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		dup2((*cmd_list)->input, STDIN_FILENO);
		dup2((*cmd_list)->output, STDOUT_FILENO);
		close_all_fd(data);
		cmd_array = fill_cmd_array(*cmd_list);
		execve((*cmd_list)->path, cmd_array, envp);
		printf("bash: %s: %s\n", (*cmd_list)->command, strerror(errno));
		return (FAIL);
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
	printf("bash: %s: command not found\n", (*cmd_list)->command);
	return (127);
}

int	exec_pipes(char **envp, t_cmd **cmd_list, t_data *data)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	while ((*cmd_list) && ((*cmd_list)->delimiter == PIPE
			|| ((*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)))
	{
		if ((*cmd_list)->is_builtin)
			exit_code = exec_builtin(*cmd_list, data);
		else if ((*cmd_list)->path)
		{
			if (!exec_command_pipe(&exit_code, envp, cmd_list, data))
				return (FAIL);
		}
		else
			exit_code = (handle_error(cmd_list));
		close_fd(cmd_list);
		*cmd_list = (*cmd_list)->next;
	}
	return (exit_code);
}
