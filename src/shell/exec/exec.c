/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 14:54:41 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_cmd_array(t_cmd *cmd_list)
{
	char	**cmd_array;
	int		i;

	if (!cmd_list->command)
		return (NULL);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
		i++;
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		return (NULL);
	ft_memcpy(cmd_array[0], cmd_list->command, ft_strlen(cmd_list->command) + 1);
	// i = 0;
	while (cmd_list->options && cmd_list->options[++i])
		ft_memcpy(cmd_array[i + 1], cmd_list->options[i], ft_strlen(cmd_list->options[i]) + 1);
	cmd_array[++i] = NULL;
	

	return (cmd_array);
}

t_bool	exec_command(pid_t pid, char **envp, t_cmd *cmd_list)
{
	char	**cmd_array;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		cmd_array = fill_cmd_array(cmd_list);
		execve(cmd_list->path, cmd_array, envp);
	}
	return (FAIL);
}

int	exec(char **envp, t_data *data)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	t_cmd 	*cmd_list;

	cmd_list = data->cmd_list;
	cmd_list = cmd_list->left;
	exit_code = EXIT_FAILURE;
	pid = 0;
	while (cmd_list)
	{
//		if (cmd_list->is_builtin)
//			exec_builtin(cmd_list, data);
		if (cmd_list->path)
		{
			exec_command(pid, envp, cmd_list);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		cmd_list = cmd_list->left;
	}
	return (exit_code);
}
