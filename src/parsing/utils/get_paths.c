/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:51:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/25 13:55:36 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recheck_cmd_path(t_cmd **cmd_list, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!(*cmd_list)->command)
		return ;
	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	if (ft_strchr((*cmd_list)->command, '$'))
	{
		(*cmd_list)->command = transform_str(
				(*cmd_list)->command, pid_value, ret_value, data);
		(*cmd_list)->path = find_cmd_path(
				(*cmd_list)->command, NULL, data->all_paths, data);
	}
	clean_free(&pid_value);
	clean_free(&ret_value);
}

char	*get_path_executable(char *command, t_data *data)
{
	char	*path;
	int		i;
	int		j;

	printf("command = %s\n", command);
	path = NULL;
	if (!command)
		return (path);
	path = (char *)ft_calloc(1, sizeof(char) * (ft_strlen(command) - 1));
	if (!path)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	i = 2;
	j = 0;
	while (command[i])
		path[j++] = command[i++];
	path[j] = '\0';
	printf("path = %s\n", path);
	return (path);
}

char	*find_cmd_path(
	char *command, char *path, char **all_paths, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = -1;
	clean_free(&path);
	if (command && command[0] && command[0] == '/')
		return (safe_strdup(command, data));
	if (command && command[0] && command[0] == '.' && command[1])
	{
		if (command[1] == '/')
			return (get_path_executable(command, data));
		if (command[1] == '.' && command[2] && command[2] == '/')
			return (safe_strdup(command, data));
	}
	if (command && (str_is_equal(command, ".") || str_is_equal(command, "..")))
		return (NULL);
	while (all_paths && all_paths[++i])
	{
		cmd_path = safe_strjoin(all_paths[i], command, data);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		clean_free(&cmd_path);
	}
	return (NULL);
}

char	**get_paths(t_data *data)
{
	int		i;
	char	*path_variable;
	char	**all_paths;

	path_variable = get_env("PATH", data->env);
	if (!path_variable)
		return (NULL);
	all_paths = safe_split(path_variable, ':', data);
	i = -1;
	while (all_paths[++i])
		all_paths[i] = safe_strjoin_and_free(all_paths[i], "/", data);
	all_paths[i] = NULL;
	return (all_paths);
}
