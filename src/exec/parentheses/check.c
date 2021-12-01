/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:38:56 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/01 11:36:15 by efrancon         ###   ########.fr       */
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

static t_bool	check_par_lvl(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	int		parenthese;

	tmp = *cmd_list;
	while (tmp && tmp->parenthese)
	{
		parenthese = get_num_parenthese(tmp);
		if (tmp->par_lvl == 1)
			return (SUCCESS);
		tmp = tmp->next;
		if (parenthese == LAST)
			break ;
	}
	while (*cmd_list && (*cmd_list)->parenthese)
		*cmd_list = (*cmd_list)->next;
	return (FAIL);
}

t_bool	check_exec_parentheses(
		int last_exit_code, t_cmd **cmd_list, t_data *data)
{
	if (!check_par_lvl(cmd_list) || (!is_first_cmd(cmd_list, data)
			&& !can_exec_parenthese(last_exit_code, cmd_list)))
		return (FAIL);
	check_redir_parentheses(*cmd_list, data);
	return (SUCCESS);
}
