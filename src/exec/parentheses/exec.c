/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:40 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/30 19:57:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_num_parenthese(t_cmd *cmd_list)
{
	if (cmd_list && cmd_list->next && cmd_list->next->delimiter == PIPE)
	{
		while (cmd_list && cmd_list->next && cmd_list->next->delimiter == PIPE)
			cmd_list = cmd_list->next;
	}
	return (cmd_list->parenthese);
}

static void	exec_cmd_parenthese(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	t_bool	error_file;
	int		parenthese;

	exit_code = EXIT_SUCCESS;
	while (*cmd_list && (*cmd_list)->parenthese)
	{
		parenthese = get_num_parenthese(*cmd_list);
		// printf("Exec par = %s | parenthese = %d\n", (*cmd_list)->command, parenthese);
		error_file = open_files(&exit_code, *cmd_list, data);
		if (!handle_execution(&exit_code, cmd_list, data))
		{
			handle_error_msg_exec(
				&exit_code, (*cmd_list)->command, (*cmd_list)->error_output);
			*cmd_list = (*cmd_list)->next;
			check_exit_code(exit_code, cmd_list);
		}
		if (parenthese == LAST)
			break ;
	}
	clean_data(data);
	exit(exit_code);
}

int	exec_parentheses(int last_exit_code, t_cmd **cmd_list, t_data *data)
{
	int	exit_code;
	int	pid;
	int	status;
	int	parenthese;

	exit_code = 0;
	status = 0;
	if (!check_exec_parentheses(last_exit_code, cmd_list, data))
		return (1);
	// print_list(data->cmd_list);
	pid = fork();
	if (pid < 0)
		return (exit_error_bool("fork()", data));
	if (pid == CHILD)
		exec_cmd_parenthese(cmd_list, data);
	while (*cmd_list && (*cmd_list)->parenthese)
	{
		parenthese = (*cmd_list)->parenthese;
		close_fd(cmd_list, data);
		*cmd_list = (*cmd_list)->next;
		if (parenthese == LAST)
			break ;
	}
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		handle_status(status, &exit_code);
	check_exit_code(exit_code, cmd_list);
	return (exit_code);
}