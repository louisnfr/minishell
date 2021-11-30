/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:57:51 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/30 12:28:38 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipe_opt_args(t_cmd *tmp)
{
	int	i;

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
			printf("Arg[%d] : |%s|\t", i, tmp->args[i]);
		printf("\n");
	}
}

void	print_files(t_cmd *tmp)
{
	int	i;

	if (tmp->files)
	{
		i = -1;
		while (tmp->files[++i])
			printf("Files[%d] : |%s| | redir = %d\t",
				i, tmp->files[i], tmp->redirection[i]);
		printf("\n");
	}
}

void	print_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	printf("\n");
	while (tmp)
	{
		printf("Cmd : %s\n", tmp->command);
		printf("Is_builtin : %d\n", tmp->is_builtin);
		printf("INPUT : %d  |  OUTPUT : %d  |  ERROR : %d\n",
			tmp->input, tmp->output, tmp->error_output);
		print_pipe_opt_args(tmp);
		if (tmp->path)
			printf("Path : %s\n", tmp->path);
		if (tmp->delimiter)
			printf("Delimiter = %d\n", tmp->delimiter);
		print_files(tmp);
		printf("Parenthese = %d\n", tmp->parenthese);
		if (tmp->par_lvl)
			printf("PAR LVL = %d\n", tmp->par_lvl);
		tmp = tmp->next;
		printf("\n");
	}
}
