/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/11 12:29:36 by EugenieFran      ###   ########.fr       */
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
	int *exit_code, char **envp, t_cmd **cmd_list, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	if ((*cmd_list)->is_builtin)
	{
		*exit_code = exec_builtin(*cmd_list, data);
		*cmd_list = (*cmd_list)->next;
		check_exit_code(*exit_code, cmd_list);
	}
	else if ((*cmd_list)->path)
	{
		exec_command(pid, envp, *cmd_list);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*exit_code = WEXITSTATUS(status);
		*cmd_list = (*cmd_list)->next;
		check_exit_code(*exit_code, cmd_list);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int	exec(char **envp, t_data *data)
{
	int		exit_code;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list->next;
	exit_code = EXIT_FAILURE;
	while (cmd_list)
	{
		if (cmd_list->next && cmd_list->next->delimiter == PIPE)
			manage_pipes(&cmd_list);
		if (!handle_execution(&exit_code, envp, &cmd_list, data))
		{
			exit_code = 127;
			printf("bash: %s: command not found\n", cmd_list->command);
			cmd_list = cmd_list->next;
		}
	}
	data->ret_value = exit_code;
	return (exit_code);
}
