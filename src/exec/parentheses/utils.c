/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:35:58 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:35:53 by efrancon         ###   ########.fr       */
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

void	close_fd_parentheses(t_cmd **cmd_list, t_data *data)
{
	int	parenthese;

	while (*cmd_list && (*cmd_list)->parenthese)
	{
		parenthese = (*cmd_list)->parenthese;
		close_fd(cmd_list, NULL, data);
		*cmd_list = (*cmd_list)->next;
		if (parenthese == LAST)
			break ;
	}
}

t_bool	copy_last_file(char	*file, t_cmd **cmd_list, t_data *data)
{
	(*cmd_list)->files = (char **)ft_calloc(1, sizeof(char *) * 2);
	if (!(*cmd_list)->files)
		return (FAIL);
	(*cmd_list)->files[0] = safe_strdup(file, data);
	(*cmd_list)->files[1] = NULL;
	return (SUCCESS);
}

t_bool	copy_last_redirection(
	t_bool is_first, int redirection, t_cmd **cmd_list)
{
	if (redirection == RIGHT_MARK && !is_first)
		redirection = DOUBLE_RIGHT_MARK;
	(*cmd_list)->redirection = (int *)ft_calloc(1, sizeof(int) * 1);
	if (!(*cmd_list)->redirection)
		return (FAIL);
	(*cmd_list)->redirection[0] = redirection;
	return (SUCCESS);
}

void	change_last_redirection(t_cmd **cmd_list)
{
	int		i;

	i = -1;
	while ((*cmd_list)->files[i + 1])
		i++;
	(*cmd_list)->redirection[i] = DOUBLE_RIGHT_MARK;
}
