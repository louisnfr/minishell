/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:56 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 23:11:27 by EugenieFran      ###   ########.fr       */
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

void	fill_args(char **cmd_array, int *i, t_cmd *cmd_list, t_data *data)
{
	int		j;
	char	*ret_value;

	j = 0;
	ret_value = ft_itoa(data->ret_value);
	while (cmd_list->args && cmd_list->args[j])
	{
		if (ft_strchr(cmd_list->args[j], '*'))
			fill_wildcard_arg(&(*cmd_array), i, cmd_list->args[j]);
		else
		{
			cmd_array[*i + 1] = ft_strdup(cmd_list->args[j]);
			(*i)++;
		}
		j++;
	}
	clean_free(&ret_value);
}

char	**fill_cmd_array(t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;
	int		i;

	if (!cmd_list || !cmd_list->command)
		return (NULL);
	cmd_array = NULL;
	cmd_array = malloc_cmd_array(cmd_array, cmd_list);
	if (!cmd_array)
		return (NULL);
	parse_special_value(cmd_list, data);
	cmd_array[0] = ft_strdup(cmd_list->command);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->options[i]);
		i++;
	}
	fill_args(&(*cmd_array), &i, cmd_list, data);
	cmd_array[++i] = NULL;
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

t_bool	error_exec_cmd(char *error_msg, int exit_code, t_cmd *cmd_list, t_data *data)
{
	display_error_message(
		cmd_list->command, error_msg, cmd_list->error_output);
	close_fd(&cmd_list);
	clean_data(data);
	exit(exit_code);
	return (FAIL);
}

t_bool	exec_command(pid_t pid, t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;
	char	**envp;

	cmd_list->path = find_cmd_path(cmd_list->command, get_paths(data));
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
		envp = env_to_char(data->env);
		if (!cmd_list->path)
			return (error_exec_cmd("No such file or directory", 127, cmd_list, data));
		execve(cmd_list->path, cmd_array, envp);
		return (error_exec_cmd(strerror(errno), get_error_code(), cmd_list, data));
	}
	return (SUCCESS);
}
