/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:20 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/30 16:54:47 by efrancon         ###   ########.fr       */
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
		// if (*cmd_list && (*cmd_list)->parenthese)
		if (*cmd_list && ((*cmd_list)->parenthese == FIRST
				|| (*cmd_list)->parenthese == LAST))
		{
			while (*cmd_list && (*cmd_list)->parenthese != LAST)
				*cmd_list = (*cmd_list)->next;
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

t_bool	handle_execution(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (!(*cmd_list)->path)
		recheck_cmd_path(cmd_list, data);
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

static void	exec_command(int *exit_code, t_cmd **cmd_list, t_data *data)
{
	if (*cmd_list && (*cmd_list)->parenthese)
	{
		*exit_code = exec_parentheses(*exit_code, cmd_list, data);
		// printf("************************** Command = %s\n", (*cmd_list)->command);
	}
	else if (!handle_execution(exit_code, cmd_list, data))
	{
		handle_error_msg_exec(
			exit_code, (*cmd_list)->command, (*cmd_list)->error_output);
		*cmd_list = (*cmd_list)->next;
		check_exit_code(*exit_code, cmd_list);
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
			data->ret_value = exit_code;
			cmd_list = cmd_list->next;
			continue ;
		}
		exec_command(&exit_code, &cmd_list, data);
		data->ret_value = exit_code;
	}
	return (exit_code);
}
