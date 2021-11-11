/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:20 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/11 22:41:46 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_code(int exit_code, t_cmd **cmd_list)
{
	if (!*cmd_list)
		return ;
	if ((exit_code && (*cmd_list)->delimiter == AND)
		|| (!exit_code && (*cmd_list)->delimiter == OR))
	{
		if (*cmd_list && (*cmd_list)->parenthese == FIRST)
		{
			while (*cmd_list && (*cmd_list)->parenthese)
				*cmd_list = (*cmd_list)->next;
		}
		else if (*cmd_list && (*cmd_list)->nb_of_pipes)
		{
			*cmd_list = (*cmd_list)->next;
			while (*cmd_list && ((*cmd_list)->delimiter == PIPE
					|| (*cmd_list)->delimiter == OR))
				*cmd_list = (*cmd_list)->next;
		}
		else
			*cmd_list = (*cmd_list)->next;
	}
}

void	handle_bin_command(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (exec_bin_command(&pid, *cmd_list, data))
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*exit_code = WEXITSTATUS(status);
		close_fd(cmd_list);
	}
}

t_bool	handle_execution(
	int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (*cmd_list && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
		*exit_code = exec_pipes(cmd_list, data);
	else if (*cmd_list && (*cmd_list)->is_builtin)
	{
		*exit_code = exec_builtin(*cmd_list, data);
		*cmd_list = (*cmd_list)->next;
	}
	else if (*cmd_list && (*cmd_list)->path)
	{
		handle_bin_command(exit_code, cmd_list, data);
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

void	handle_error_msg_exec(int *exit_code, char *command, int fd_error)
{
	if (command && command[0] != '\0')
	{
		*exit_code = 127;
		if (ft_strchr(command, '/'))
			display_error_message(
				command, "No such file or directory", fd_error);
		else
			display_error_message(command, "command not found", fd_error);
	}
	else
		*exit_code = 0;
}

int	exec(t_data *data)
{
	int		exit_code;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list->next;
	exit_code = EXIT_FAILURE;
	while (cmd_list)
	{
		if (cmd_list && cmd_list->parenthese)
			exit_code = exec_parentheses(exit_code, &cmd_list, data);
		else if (!handle_execution(&exit_code, &cmd_list, data))
		{
			handle_error_msg_exec(
				&exit_code, cmd_list->command, cmd_list->error_output);
			cmd_list = cmd_list->next;
			check_exit_code(exit_code, &cmd_list);
		}
		data->ret_value = exit_code;
	}
	return (exit_code);
}
