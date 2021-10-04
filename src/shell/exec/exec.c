/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 18:19:34 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_cmd_array(t_cmd *cmd_list)
{
	char	**cmd_array;
	int		i;
	int		j;

	if (!cmd_list->command)
		return (NULL);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
		i++;
	j = 0;
	while (cmd_list->args && cmd_list->args[j++])
		i++;
	cmd_array = NULL;
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
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

void	check_exit_code(int exit_code, t_cmd **cmd_list)
{
	if (*cmd_list)
	{
		if ((exit_code && (*cmd_list)->delimiter == AND)
			|| (!exit_code && (*cmd_list)->delimiter == OR))
			*cmd_list = (*cmd_list)->next;
	}
}

int	exec(char **envp, t_data *data)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	cmd_list = cmd_list->next;
	exit_code = EXIT_FAILURE;
	pid = 0;
	while (cmd_list)
	{
		if (cmd_list->is_builtin)
		{
			exit_code = exec_builtin(cmd_list, data);
			cmd_list = cmd_list->next;
			check_exit_code(exit_code, &cmd_list);
		}
		else if (cmd_list->path)
		{
			exec_command(pid, envp, cmd_list);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			cmd_list = cmd_list->next;
			check_exit_code(exit_code, &cmd_list);
		}
		else
		{
			exit_code = 127;
			printf("bash: %s: command not found\n", cmd_list->command);
			cmd_list = cmd_list->next;
		}
	}
	data->ret_value = exit_code;
	return (exit_code);
}
