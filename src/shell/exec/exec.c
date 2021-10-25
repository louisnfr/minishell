/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/22 18:39:19 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_code(int exit_code, t_cmd **cmd_list)
{
	if (*cmd_list)
	{
		if ((exit_code && (*cmd_list)->delimiter == AND)
			|| (!exit_code && (*cmd_list)->delimiter == OR))
			*cmd_list = (*cmd_list)->next;
	}
}

t_bool	handle_execution(
	int *exit_code, t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	if ((*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
		*exit_code = exec_pipes(cmd_list, data);
	else if (*cmd_list && (*cmd_list)->is_builtin)
	{
		*exit_code = exec_builtin(*cmd_list, data);
		*cmd_list = (*cmd_list)->next;
	}
	else if (*cmd_list && (*cmd_list)->path)
	{
		if (exec_command(pid, *cmd_list, data))
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				*exit_code = WEXITSTATUS(status);
			close_fd(cmd_list);
		}
		*cmd_list = (*cmd_list)->next;
	}
	else
	{
		parse_special_value(*cmd_list, data);
		return (FAIL);
	}
	check_exit_code(*exit_code, cmd_list);
	return (SUCCESS);
}

void	handle_error_msg_exec(char *command, int fd_error)
{
	if (ft_strchr(command, '/'))
		display_error_message(command, "No such file or directory", fd_error);
	else
		display_error_message(command, "command not found", fd_error);
}

int	exec(t_data *data)
{
	int		exit_code;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list->next;
	exit_code = EXIT_FAILURE;
	while (cmd_list)
	{
		if (!handle_execution(&exit_code, &cmd_list, data))
		{
			exit_code = 127;
			handle_error_msg_exec(cmd_list->command, cmd_list->error_output);
			cmd_list = cmd_list->next;
		}
		data->ret_value = exit_code;
	}
	return (exit_code);
}

/*
int	exec(t_data *data)
{
	int		exit_code;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list->next;
	exit_code = EXIT_FAILURE;
	while (cmd_list)
	{
		if (!handle_execution(&exit_code, &cmd_list, data))
		{
			exit_code = 127;
			handle_error_msg_exec(cmd_list->command, cmd_list->error_output);
			cmd_list = cmd_list->next;
		}
		data->ret_value = exit_code;
	}
	return (exit_code);
}
*/
