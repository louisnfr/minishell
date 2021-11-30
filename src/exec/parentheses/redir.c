/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:11:35 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/30 17:32:25 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_last_file(char	*file, t_cmd **cmd_list, t_data *data)
{
	(*cmd_list)->files = (char **)ft_calloc(1, sizeof(char *) * 2);
	if (!(*cmd_list)->files)
		exit_error_bool("malloc()", data);
	(*cmd_list)->files[0] = safe_strdup(file, data);
	(*cmd_list)->files[1] = NULL;
}

static void	copy_last_redirection(
	t_bool is_first, int redirection, t_cmd **cmd_list, t_data *data)
{
	if (redirection == RIGHT_MARK && !is_first)
		redirection = DOUBLE_RIGHT_MARK;
	(*cmd_list)->redirection = (int *)ft_calloc(1, sizeof(int) * 1);
	if (!(*cmd_list)->redirection)
		exit_error_bool("malloc()", data);
	(*cmd_list)->redirection[0] = redirection;
}

static void	get_last_file(
	int *redirection, char **file, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_bool	change_redir;

	*file = NULL;
	change_redir = FALSE;
	while (cmd_list && cmd_list->parenthese != LAST)
	{
		if (!cmd_list->files && !cmd_list->nb_of_pipes)
			change_redir = TRUE;
		cmd_list = cmd_list->next;
	}
	if (cmd_list && cmd_list->files && change_redir)
	{
		i = 0;
		while (cmd_list->files[i + 1])
			i++;
		if (cmd_list->redirection[i] == RIGHT_MARK
			|| cmd_list->redirection[i] == DOUBLE_RIGHT_MARK)
		{
			*file = safe_strdup(cmd_list->files[i], data);
			*redirection = cmd_list->redirection[i];
		}
	}
}

void	check_redir_parentheses(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	*file;
	int		redirection;
	t_bool	is_first;

	get_last_file(&redirection, &file, cmd_list, data);
	if (!file)
		return ;
	is_first = TRUE;
	while (cmd_list && cmd_list->parenthese != LAST)
	{
		if (!cmd_list->files && !cmd_list->nb_of_pipes)
		{
			copy_last_file(file, &cmd_list, data);
			copy_last_redirection(is_first, redirection, &cmd_list, data);
			is_first = FALSE;
		}
		cmd_list = cmd_list->next;
	}
	i = -1;
	while (cmd_list->files[i + 1])
		i++;
	cmd_list->redirection[i] = DOUBLE_RIGHT_MARK;
	// printf("------------------------------ Command = %s | redir = %d\n", cmd_list->command, cmd_list->redirection[i]);
	clean_free(&file);
}
