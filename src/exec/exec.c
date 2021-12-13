/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:20 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:38:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_code(int exit_code, t_cmd **cmd_list, t_data *data)
{
	if (*cmd_list && ((exit_code && (*cmd_list)->delimiter == AND)
			|| (!exit_code && (*cmd_list)->delimiter == OR)))
	{
		if (*cmd_list && (*cmd_list)->parenthese == FIRST)
		{
			while (*cmd_list && (*cmd_list)->parenthese != LAST)
				get_next_cmd(cmd_list, data);
			get_next_cmd(cmd_list, data);
		}
		else if (*cmd_list && (*cmd_list)->nb_of_pipes)
		{
			get_next_cmd(cmd_list, data);
			while (*cmd_list && ((*cmd_list)->delimiter == PIPE
					|| (*cmd_list)->delimiter == OR))
				get_next_cmd(cmd_list, data);
		}
		else if (*cmd_list && (*cmd_list)->delimiter == OR)
		{
			while (*cmd_list && (*cmd_list)->delimiter == OR)
				get_next_cmd(cmd_list, data);
		}
		else if (*cmd_list)
			get_next_cmd(cmd_list, data);
	}
}

static t_bool	handle_other_cases(
	int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (*cmd_list && (!(*cmd_list)->command || !(*cmd_list)->command[0]))
	{
		close_fd(cmd_list, NULL, data);
		*exit_code = 0;
		*cmd_list = (*cmd_list)->next;
		return (SUCCESS);
	}
	parse_special_value(*cmd_list, data);
	return (FAIL);
}

t_bool	handle_execution(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (!(*cmd_list)->path)
		recheck_cmd_path(cmd_list, data);
	if (*cmd_list && (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
		*exit_code = exec_pipes(cmd_list, data);
	else if (*cmd_list && (*cmd_list)->is_builtin)
	{
		*exit_code = exec_builtin(*cmd_list, data);
		close_fd(cmd_list, NULL, data);
		*cmd_list = (*cmd_list)->next;
	}
	else if (*cmd_list && (*cmd_list)->path)
	{
		handle_bin_command(exit_code, cmd_list, data);
		*cmd_list = (*cmd_list)->next;
	}
	else
		return (handle_other_cases(exit_code, cmd_list, data));
	if (*cmd_list)
		check_exit_code(*exit_code, cmd_list, data);
	return (SUCCESS);
}

static void	exec_command(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (*cmd_list && (*cmd_list)->parenthese)
		*exit_code = exec_parentheses(*exit_code, cmd_list, data);
	else if (!handle_execution(exit_code, cmd_list, data))
	{
		handle_error_msg_exec(
			exit_code, (*cmd_list)->command, (*cmd_list)->error_output);
		close_fd(cmd_list, NULL, data);
		*cmd_list = (*cmd_list)->next;
		check_exit_code(*exit_code, cmd_list, data);
	}
}

int	exec(t_data *data)
{
	int		exit_code;
	t_cmd	*cmd_list;
	t_bool	error_file;

	if (!init_exec(&exit_code, &error_file, &cmd_list, data))
		return (exit_code);
	while (cmd_list)
	{
		if ((!cmd_list->next && !cmd_list->parenthese)
			|| ((cmd_list->next && cmd_list->next->delimiter != PIPE)
				&& !cmd_list->parenthese))
			error_file = open_files(&exit_code, cmd_list, data);
		if (error_file)
		{
			close_fd(&cmd_list, NULL, data);
			data->ret_value = exit_code;
			cmd_list = cmd_list->next;
			continue ;
		}
		exec_command(&exit_code, &cmd_list, data);
		data->ret_value = exit_code;
	}
	return (exit_code);
}
