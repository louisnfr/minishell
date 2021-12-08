/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:40 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/08 17:11:26 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	recheck_par_lvl(int par_lvl, t_cmd *tmp)
{
	int	parenthese;

	if (par_lvl < 2)
		return (SUCCESS);
	while (tmp && tmp->parenthese)
	{
		parenthese = get_num_parenthese(tmp);
		if (tmp->par_lvl == par_lvl - 1)
			return (SUCCESS);
		tmp = tmp->next;
		if (parenthese == LAST)
			break ;
	}
	return (FAIL);
}

static void	recheck_num_parenthese(
	int exit_code, int *parenthese, t_cmd *cmd_list)
{
	if (cmd_list && cmd_list->next
		&& cmd_list->next->delimiter == OR && !exit_code)
	{
		while (cmd_list && cmd_list->next && cmd_list->next->delimiter == OR)
			cmd_list = cmd_list->next;
		*parenthese = cmd_list->parenthese;
	}
	else if (cmd_list && cmd_list->next
		&& cmd_list->next->delimiter == AND && exit_code)
	{
		while (cmd_list && cmd_list->next && cmd_list->next->delimiter == AND)
			cmd_list = cmd_list->next;
		*parenthese = cmd_list->parenthese;
	}
}

static t_bool	exec_must_stop(
	int exit_code, int parenthese, t_cmd *tmp, t_cmd **cmd_list)
{
	recheck_num_parenthese(exit_code, &parenthese, *cmd_list);
	if (parenthese == LAST)
		return (TRUE);
	if (*cmd_list && !recheck_par_lvl((*cmd_list)->par_lvl, tmp))
	{
		parenthese = get_num_parenthese(*cmd_list);
		*cmd_list = (*cmd_list)->next;
		if (parenthese == LAST)
			return (TRUE);
	}
	return (FALSE);
}

static void	exec_cmd_parenthese(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	int		parenthese;
	t_cmd	*tmp;

	tmp = *cmd_list;
	exit_code = EXIT_SUCCESS;
	while (*cmd_list && (*cmd_list)->parenthese)
	{
		parenthese = get_num_parenthese(*cmd_list);
		if (open_files(&exit_code, *cmd_list, data))
			break ;
		else if (!handle_execution(&exit_code, cmd_list, data))
		{
			handle_error_msg_exec(
				&exit_code, (*cmd_list)->command, (*cmd_list)->error_output);
			close_fd(cmd_list, data);
			*cmd_list = (*cmd_list)->next;
			check_exit_code(exit_code, cmd_list);
		}
		if (exec_must_stop(exit_code, parenthese, tmp, cmd_list))
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

	exit_code = 0;
	status = 0;
	if (!check_exec_parentheses(last_exit_code, cmd_list, data))
		return (1);
	pid = fork();
	if (pid < 0)
		return (exit_error_bool("fork()", data));
	if (pid == CHILD)
		exec_cmd_parenthese(cmd_list, data);
	close_fd_parentheses(cmd_list, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		handle_status(status, &exit_code);
	check_exit_code(exit_code, cmd_list);
	return (exit_code);
}
