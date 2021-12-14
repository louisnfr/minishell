/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:40 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 14:02:13 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	recheck_num_parenthese(
	int exit_code, int *parenthese, t_cmd *cmd_list)
{
	if (cmd_list && !exit_code && cmd_list->next
		&& cmd_list->next->delimiter == OR)
	{
		while (cmd_list && cmd_list->next && cmd_list->next->delimiter == OR)
			cmd_list = cmd_list->next;
		*parenthese = cmd_list->parenthese;
	}
	else if (cmd_list && exit_code && cmd_list->next
		&& cmd_list->next->delimiter == AND)
	{
		while (cmd_list && cmd_list->next && cmd_list->next->delimiter == AND)
			cmd_list = cmd_list->next;
		*parenthese = cmd_list->parenthese;
	}
}

static t_bool	exec_must_stop(
	int exit_code, int parenthese, t_cmd *tmp)
{
	if (parenthese == LAST)
		return (TRUE);
	recheck_num_parenthese(exit_code, &parenthese, tmp);
	if (parenthese == LAST)
		return (TRUE);
	return (FALSE);
}

static void	exec_cmd_parenthese(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	int		parenthese;
	t_cmd	*tmp;

	exit_code = EXIT_SUCCESS;
	while (*cmd_list && (*cmd_list)->parenthese)
	{
		tmp = *cmd_list;
		parenthese = get_num_parenthese(*cmd_list);
		if (open_files(&exit_code, *cmd_list, data))
			break ;
		else if (!handle_execution(&exit_code, cmd_list, data))
		{
			handle_error_msg_exec(
				&exit_code, (*cmd_list)->command, (*cmd_list)->error_output);
			close_fd(cmd_list, NULL, data);
			*cmd_list = (*cmd_list)->next;
			check_exit_code(exit_code, cmd_list, data);
		}
		if (!*cmd_list || exec_must_stop(exit_code, parenthese, tmp))
			break ;
	}
	close_all_fd(NULL, data);
	clean_data(data);
	exit(exit_code);
}

int	exec_parentheses(int last_exit_code, t_cmd **cmd_list, t_data *data)
{
	int	exit_code;
	int	pid;
	int	status;

	exit_code = 0;
	status = 0;
	if (!check_exec_parentheses(last_exit_code, cmd_list, data))
		return (1);
	pid = fork();
	if (pid < 0)
		exit_error_str(NULL, "fork()", data);
	if (pid == CHILD)
		exec_cmd_parenthese(cmd_list, data);
	close_fd_parentheses(cmd_list, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		handle_status(status, &exit_code);
	check_exit_code(exit_code, cmd_list, data);
	return (exit_code);
}
