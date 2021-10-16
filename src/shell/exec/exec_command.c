/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:56 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/16 14:30:05 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_cmd_array(char **cmd_array, t_cmd *cmd_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_list->options && cmd_list->options[i])
		i++;
	j = 0;
	while (cmd_list->args && cmd_list->args[j++])
		i++;
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		return (NULL);
	return (cmd_array);
}

char	**fill_cmd_array(t_cmd *cmd_list)
{
	char	**cmd_array;
	int		i;
	int		j;

	if (!cmd_list || !cmd_list->command)
		return (NULL);
	cmd_array = NULL;
	cmd_array = malloc_cmd_array(cmd_array, cmd_list);
	if (!cmd_array)
		return (NULL);
	cmd_array[0] = ft_strdup(cmd_list->command);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->options[i]);
		i++;
	}
	j = 0;
	while (cmd_list->args && cmd_list->args[j])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->args[j++]);
		i++;
	}
	cmd_array[++i] = NULL;
	return (cmd_array);
}

t_bool	exec_command(pid_t pid, char **envp, t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;

	(void)data;
	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		if (cmd_list->input == -1 || cmd_list->output == -1)
			return (FAIL);
		if (cmd_list->redirection)
		{
			dup2(cmd_list->input, STDIN_FILENO);
			dup2(cmd_list->output, STDOUT_FILENO);
			dup2(cmd_list->error_output, STDERR_FILENO);
			close_all_fd(data);
		}
		cmd_array = fill_cmd_array(cmd_list);
		execve(cmd_list->path, cmd_array, envp);
		display_error_message(
			cmd_list->command, strerror(errno), cmd_list->error_output);
		clean_data(data);
		return (FAIL);
	}
//	else
//		wait(NULL);
	return (SUCCESS);
}
