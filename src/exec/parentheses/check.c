/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:38:56 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/08 17:17:01 by efrancon         ###   ########.fr       */
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

t_bool	check_exec_parentheses(
		int last_exit_code, t_cmd **cmd_list, t_data *data)
{
	if (!is_first_cmd(cmd_list, data)
		&& !can_exec_parenthese(last_exit_code, cmd_list))
		return (FAIL);
	check_redir_parentheses(*cmd_list, data);
	return (SUCCESS);
}
