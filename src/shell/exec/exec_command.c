/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:56 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/18 16:50:39 by EugenieFran      ###   ########.fr       */
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
	while (cmd_list->args && cmd_list->args[j])
	{
		if (ft_strchr(cmd_list->args[j], '*'))
			count_wildcard_arg(&i, cmd_list->args[j]);
		else
			i++;
		j++;
	}
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		return (NULL);
	return (cmd_array);
}

char	**fill_cmd_array(t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;
	char	*ret_value;
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
	ret_value = ft_itoa(data->ret_value);
	j = 0;
	while (cmd_list->args && cmd_list->args[j])
	{
		if (ft_strchr(cmd_list->args[j], '$') && ft_strchr(cmd_list->args[j], '?'))
			cmd_list->args[j] = transform_special_value(cmd_list->args[j], ret_value, '?');
		if (ft_strchr(cmd_list->args[j], '*'))
			fill_wildcard_arg(&(*cmd_array), &i, cmd_list->args[j]);
		else
		{
			cmd_array[i + 1] = ft_strdup(cmd_list->args[j]);
			i++;
		}
		j++;
	}
	cmd_array[++i] = NULL;
	clean_free(&ret_value);
	return (cmd_array);
}

int	get_error_code(void)
{
//	printf("errno = %d\n", errno);
	if (errno == 2)
		return (127);
	if (errno == 13)
		return (126);
	return (1);
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
		cmd_array = fill_cmd_array(cmd_list, data);
		execve(cmd_list->path, cmd_array, envp);
		display_error_message(
			cmd_list->command, strerror(errno), cmd_list->error_output);
		close_fd(&cmd_list);
		clean_data(data);
		exit(get_error_code());
		return (FAIL);
	}
	return (SUCCESS);
}
