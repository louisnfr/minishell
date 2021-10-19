/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/19 19:57:32 by lraffin          ###   ########.fr       */
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
	else if ((*cmd_list)->is_builtin)
	{
		*exit_code = exec_builtin(*cmd_list, data);
		*cmd_list = (*cmd_list)->next;
	}
	else if ((*cmd_list)->path)
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
		parse_ret_value(*cmd_list, data);
		return (FAIL);
	}
	check_exit_code(*exit_code, cmd_list);
	return (SUCCESS);
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
			display_error_message(cmd_list->command, "command not found", cmd_list->error_output);
			cmd_list = cmd_list->next;
		}
		data->ret_value = exit_code;
	}
	return (exit_code);
}
