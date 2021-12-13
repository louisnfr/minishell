/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:11:35 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 17:44:11 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_last_file(
	int *redirection, char **file, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_bool	change_redir;

	*file = NULL;
	change_redir = FALSE;
	while (cmd_list && cmd_list->parenthese != LAST)
	{
		if (!cmd_list->files && cmd_list->delimiter != PIPE)
			change_redir = TRUE;
		cmd_list = cmd_list->next;
	}
	if (cmd_list && cmd_list->files && change_redir)
	{
		i = 0;
		while (cmd_list->files[i + 1])
			i++;
		if (cmd_list->redirection[i] == RIGHT_MARK
			|| cmd_list->redirection[i] == DOUBLE_RIGHT_MARK
			|| cmd_list->redirection[i] == LEFT_MARK)
		{
			*file = safe_strdup(cmd_list->files[i], data);
			*redirection = cmd_list->redirection[i];
		}
	}
}

void	handle_left_redir(char *file, t_cmd *cmd_list, t_data *data)
{	
	t_bool	is_first;	

	is_first = TRUE;
	while (cmd_list && cmd_list->parenthese != LAST)
	{
		if (!cmd_list->files && cmd_list->delimiter != PIPE)
		{
			if (!copy_last_file(file, &cmd_list, data)
				|| !copy_last_redirection(is_first, LEFT_MARK, &cmd_list))
				exit_error_str(file, "malloc()", data);
			is_first = FALSE;
		}
		cmd_list = cmd_list->next;
	}
	if (cmd_list->delimiter == PIPE)
	{
		free(cmd_list->redirection);
		cmd_list->redirection = NULL;
		free_double_str(cmd_list->files);
		cmd_list->files = NULL;
	}
	clean_free(&file);
}

void	check_redir_parentheses(t_cmd *cmd_list, t_data *data)
{
	char	*file;
	int		redirection;
	t_bool	is_first;

	get_last_file(&redirection, &file, cmd_list, data);
	if (!file)
		return ;
	if (redirection == LEFT_MARK)
		return (handle_left_redir(file, cmd_list, data));
	is_first = TRUE;
	while (cmd_list && cmd_list->parenthese != LAST)
	{
		if (!cmd_list->files && !cmd_list->nb_of_pipes)
		{
			if (!copy_last_file(file, &cmd_list, data)
				|| !copy_last_redirection(is_first, redirection, &cmd_list))
				exit_error_str(file, "malloc()", data);
			is_first = FALSE;
		}
		cmd_list = cmd_list->next;
	}
	if (redirection == RIGHT_MARK)
		change_last_redirection(&cmd_list);
	clean_free(&file);
}
