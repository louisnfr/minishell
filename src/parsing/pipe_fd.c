/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:20:50 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/12 15:20:52 by efrancon         ###   ########.fr       */
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

int	**create_fd_array(t_cmd *cmd)
{
	int		i;
	int		nb_of_pipes;
	int		**fd_array;

	nb_of_pipes = get_nb_of_pipes(cmd);
	fd_array = (int **)ft_calloc(1, sizeof(int *) * nb_of_pipes);
	if (!fd_array)
		return (NULL);
	i = -1;
	while (++i < nb_of_pipes)
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

	i = 0;
	fd_array = create_fd_array(*cmd);
	if (!fd_array)
		return ;
	(*cmd)->output = fd_array[0][1];
	if ((*cmd)->next)
		*cmd = (*cmd)->next;
	while ((*cmd)->next && (*cmd)->next->delimiter == PIPE)
	{
		(*cmd)->input = fd_array[i][0];
		free(fd_array[i]);
		(*cmd)->output = fd_array[i + 1][1];
		*cmd = (*cmd)->next;
		i++;
	}
	(*cmd)->input = fd_array[i][0];
	free(fd_array[i]);
	free(fd_array);
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
}