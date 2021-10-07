/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 17:39:56 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd_list;
	printf("\n");
	while (tmp)
	{
		printf("Cmd : %s\n", tmp->command);
		printf("Is_builtin : %d\n", tmp->is_builtin);
		if (tmp->options)
		{
			i = -1;
			while (tmp->options[++i])
				printf("Option[%d] : %s\t", i, tmp->options[i]);
			printf("\n");
		}
		if (tmp->args)
		{
			i = -1;
			while (tmp->args[++i])
				printf("Arg[%d] : %s\t", i, tmp->args[i]);
			printf("\n");
		}
		if (tmp->path)
			printf("Path : %s\n", tmp->path);
		if (tmp->delimiter)
			printf("Delimiter = %d\n", tmp->delimiter);
		tmp = tmp->next;
		printf("\n");
	}
}

void	remove_from_list(t_cmd *cmd_list)
{
	cmd_list->is_builtin = 0;
	clean_free(&cmd_list->command);
	if (cmd_list->options)
		free_double_str(cmd_list->options);
	if (cmd_list->args)
		free_double_str(cmd_list->args);
	clean_free(&cmd_list->path);
	free(cmd_list);
	cmd_list = NULL;
}

void	clean_cmd_list(t_cmd *cmd_list)
{
	while (cmd_list->next)
	{
		remove_from_list(cmd_list);
		cmd_list = cmd_list->next;
	}
	remove_from_list(cmd_list);
	cmd_list = NULL;
}

t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (FAIL);
	setup_cmd_list(new_cmd);
	if (cmd)
	{
		new_cmd->command = ft_strdup(cmd);
		clean_free(&cmd);
	}
	new_cmd->options = options;
	if (path)
	{
		new_cmd->path = ft_strdup(path);
		clean_free(&path);
	}
	new_cmd->next = NULL;
	while ((*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	(*cmd_list)->next = new_cmd;
	(*cmd_list) = (*cmd_list)->next;
	return (SUCCESS);
}

void	setup_cmd_list(t_cmd *cmd_list)
{
	cmd_list->command = NULL;
	cmd_list->options = NULL;
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->is_builtin = FALSE;
	cmd_list->delimiter = 0;
	cmd_list->next = NULL;
}
