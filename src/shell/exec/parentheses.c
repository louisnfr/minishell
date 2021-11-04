/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:40 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:36:42 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_first_cmd(t_cmd **cmd_list, t_data *data)
{
	return (*cmd_list == data->cmd_list->next);
}

static t_bool	can_exec_parenthese(int last_exit_code, t_cmd **cmd_list)
{
	if (*cmd_list)
	{
		if ((last_exit_code && (*cmd_list)->delimiter == AND)
			|| (!last_exit_code && (*cmd_list)->delimiter == OR))
		{
			while (*cmd_list && (*cmd_list)->parenthese)
				*cmd_list = (*cmd_list)->next;
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	exec_cmd_parenthese(t_cmd **cmd_list, t_data *data)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	while (*cmd_list && (*cmd_list)->parenthese)
	{
		if (!handle_execution(&exit_code, cmd_list, data))
		{
			exit_code = 127;
			handle_error_msg_exec(
				(*cmd_list)->command, (*cmd_list)->error_output);
			*cmd_list = (*cmd_list)->next;
			check_exit_code(exit_code, cmd_list);
		}
	}
	close_all_fd(data);
	clean_data(data);
	exit(exit_code);
}

int	exec_parentheses(int last_exit_code, t_cmd **cmd_list, t_data *data)
{
	int	exit_code;
	int	pid;
	int	status;

	if (!is_first_cmd(cmd_list, data)
		&& !can_exec_parenthese(last_exit_code, cmd_list))
		return (SUCCESS);
	pid = fork();
	if (pid == CHILD)
		exec_cmd_parenthese(cmd_list, data);
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	while (*cmd_list && (*cmd_list)->parenthese)
		*cmd_list = (*cmd_list)->next;
	check_exit_code(exit_code, cmd_list);
	return (exit_code);
}
