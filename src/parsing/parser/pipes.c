/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:59:53 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 19:54:40 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_of_pipes(t_cmd *cmd)
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

static int	**create_fd_array(int *nb_of_pipes, t_cmd *cmd, t_data *data)
{
	int		i;
	int		**fd_array;

	*nb_of_pipes = get_nb_of_pipes(cmd);
	fd_array = (int **)ft_calloc(1, sizeof(int *) * *nb_of_pipes);
	if (!fd_array)
		exit_error_str(NULL, "malloc()", data);
	i = -1;
	while (++i < *nb_of_pipes)
	{
		fd_array[i] = (int *)ft_calloc(1, sizeof(int) * 2);
		if (!fd_array[i])
		{
			free_fd_array(i, fd_array);
			exit_error_strs(NULL, "malloc()", data);
		}
		if (pipe(fd_array[i]) == -1)
		{
			free_fd_array(i + 1, fd_array);
			exit_error_strs(NULL, "pipe()", data);
		}
	}
	return (fd_array);
}

static t_bool	copy_fd_array(int **fd_array, int nb_of_pipes, t_cmd **cmd)
{
	int	i;

	(*cmd)->pipe_fd = (int **)ft_calloc(1, sizeof(int *) * nb_of_pipes);
	if (!(*cmd)->pipe_fd)
		return (FAIL);
	i = -1;
	while (++i < nb_of_pipes)
	{
		(*cmd)->pipe_fd[i] = (int *)ft_calloc(1, sizeof(int) * 2);
		if (!(*cmd)->pipe_fd[i])
			return (FAIL);
		(*cmd)->pipe_fd[i][0] = fd_array[i][0];
		(*cmd)->pipe_fd[i][1] = fd_array[i][1];
	}
	(*cmd)->nb_of_pipes = nb_of_pipes;
	return (SUCCESS);
}

static void	fill_fd_array(t_cmd **cmd, t_data *data)
{
	int	i;
	int	**fd_array;
	int	nb_of_pipes;

	i = 0;
	fd_array = create_fd_array(&nb_of_pipes, *cmd, data);
	if (!copy_fd_array(fd_array, nb_of_pipes, cmd))
		exit_error_fd_array(fd_array, nb_of_pipes, data);
	(*cmd)->output = fd_array[0][1];
	if ((*cmd)->next)
		*cmd = (*cmd)->next;
	while ((*cmd)->next && (*cmd)->next->delimiter == PIPE)
	{
		copy_fd_array(fd_array, nb_of_pipes, cmd);
		if (!(*cmd)->heredoc)
			(*cmd)->input = fd_array[i][0];
		(*cmd)->output = fd_array[i + 1][1];
		*cmd = (*cmd)->next;
		i++;
	}
	copy_fd_array(fd_array, nb_of_pipes, cmd);
	if (!(*cmd)->heredoc)
		(*cmd)->input = fd_array[i][0];
	free_fd_array(nb_of_pipes, fd_array);
}

void	parse_pipes(t_cmd *cmd_list, t_data *data)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd->next)
	{
		if (cmd->next->delimiter == PIPE)
			fill_fd_array(&cmd, data);
		if (cmd && cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}
