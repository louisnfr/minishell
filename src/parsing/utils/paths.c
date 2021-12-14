/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:51:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 13:28:14 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_executable(char *command, t_data *data)
{
	char	*path;
	int		i;
	int		j;

	path = NULL;
	if (!command)
		return (path);
	path = (char *)ft_calloc(1, sizeof(char) * (ft_strlen(command) - 1));
	if (!path)
	{
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(NULL, "malloc()", data);
	}
	i = 2;
	j = 0;
	while (command[i])
		path[j++] = command[i++];
	path[j] = '\0';
	return (path);
}

static char	*get_path_command(char *command, char **all_paths, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (all_paths && all_paths[++i])
	{
		cmd_path = safe_strjoin(all_paths[i], command, data);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		clean_free(&cmd_path);
	}
	return (NULL);
}

char	*find_cmd_path(
	char *command, char *path, char **all_paths, t_data *data)
{
	clean_free(&path);
	if (command && command[0] && command[0] == '/')
	{
		if (access(command, F_OK) == 0)
			return (safe_strdup(command, data));
		return (NULL);
	}
	if (command && command[0] && command[0] == '.' && command[1])
	{
		if (command[1] == '/')
			return (get_path_executable(command, data));
		if (command[1] == '.' && command[2] && command[2] == '/')
			return (safe_strdup(command, data));
	}
	if (command && (str_is_equal(command, ".") || str_is_equal(command, "..")))
		return (NULL);
	return (get_path_command(command, all_paths, data));
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
	{
		all_paths[i] = safe_strjoin_and_free2(
				all_paths[i], "/", data, all_paths);
	}
	all_paths[i] = NULL;
	return (all_paths);
}
