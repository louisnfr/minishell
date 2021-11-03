/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:20:50 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/02 19:59:51 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_of_pipes(t_cmd *cmd)
{
	int		nb_of_pipes;

	nb_of_pipes = 0;
	cmd = cmd->next;
	while (cmd)
	{
		if (cmd && cmd->delimiter == PIPE)
		{
			while (cmd && cmd->delimiter == PIPE)
			{
				nb_of_pipes++;
				cmd = cmd->next;
			}
			break ;
		}
		if (cmd && cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (nb_of_pipes);
}

int	**create_fd_array(int *nb_of_pipes, t_cmd *cmd)
{
	int		i;
	int		**fd_array;

	*nb_of_pipes = get_nb_of_pipes(cmd);
	fd_array = (int **)ft_calloc(1, sizeof(int *) * *nb_of_pipes);
	if (!fd_array)
		return (NULL);
	i = -1;
	while (++i < *nb_of_pipes)
	{
		fd_array[i] = (int *)ft_calloc(1, sizeof(int) * 2);
		if (!fd_array[i])
			return (NULL);
		if (pipe(fd_array[i]) == -1)
			return (NULL);
	}
	return (fd_array);
}

void	fill_fd_array(t_cmd **cmd)
{
	int	i;
	int	**fd_array;
	int	nb_of_pipes;

	i = 0;
	fd_array = create_fd_array(&nb_of_pipes, *cmd);
	if (!fd_array)
		return ;
	(*cmd)->pipe_fd = fd_array;
	(*cmd)->nb_of_pipes = nb_of_pipes;
	(*cmd)->output = fd_array[0][1];
	if ((*cmd)->next)
		*cmd = (*cmd)->next;
	while ((*cmd)->next && (*cmd)->next->delimiter == PIPE)
	{
		(*cmd)->pipe_fd = fd_array;
		(*cmd)->nb_of_pipes = nb_of_pipes;
		(*cmd)->input = fd_array[i][0];
//		free(fd_array[i]);
		(*cmd)->output = fd_array[i + 1][1];
		*cmd = (*cmd)->next;
		i++;
	}
	(*cmd)->pipe_fd = fd_array;
	(*cmd)->nb_of_pipes = nb_of_pipes;
	(*cmd)->input = fd_array[i][0];
//	free(fd_array[i]);
//	free(fd_array);
}

void	parse_pipes(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd->next)
	{
		if (cmd->next->delimiter == PIPE)
			fill_fd_array(&cmd);
		if (cmd && cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
/*	printf("CMD = %s\n", cmd_list->command);
	if (cmd_list && cmd_list->next && cmd_list->next->input > 2)
			cmd_list->pipe_out = &cmd_list->next->input;
	}
	while (cmd_list && cmd_list->next)
	{
		if (cmd_list && cmd_list->next && cmd_list->output > 2)
			cmd_list->next->pipe_in = &cmd_list->output;
		if (cmd_list && cmd_list->next && cmd_list->input > 2)
			cmd_list->pipe_out = &cmd_list->next->input;
		cmd_list = cmd_list->next;
	}
*/
}
