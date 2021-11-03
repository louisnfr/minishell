/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/03 20:47:44 by EugenieFran      ###   ########.fr       */
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
		printf("INPUT : %d  |  OUTPUT : %d  |  ERROR : %d\n", tmp->input, tmp->output, tmp->error_output);
		if (tmp->pipe_fd)
		{
			i = -1;
			while (++i < tmp->nb_of_pipes)
				printf("[%d][%d]\n", tmp->pipe_fd[i][0], tmp->pipe_fd[i][1]);
			printf("nb_of_pipes : %d\n", tmp->nb_of_pipes);
		}
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
		if (tmp->redirection)
			printf("Redirection = %d\n", tmp->redirection);
//		if (tmp->parenthese)
		printf("Parenthese = %d\n", tmp->parenthese);
		tmp = tmp->next;
		printf("\n");
	}
}

t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
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
	cmd_list->redirection = 0;
	cmd_list->parenthese = OUT;
	cmd_list->input = 0;
	cmd_list->output = 1;
	cmd_list->error_output = 2;
	cmd_list->pipe_fd = NULL;
	cmd_list->nb_of_pipes = 0;
	cmd_list->heredoc = NULL;
	cmd_list->heredoc_delimiter = NULL;
	cmd_list->next = NULL;
}
