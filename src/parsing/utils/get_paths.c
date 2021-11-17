/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:51:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 16:08:18 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_executable(char *command, t_data *data)
{
	char	*path;
	int		i;
	int		j;

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
	if (command && command[0] && command[0] == '.'
		&& command[1] && command[1] == '/')
		return (get_path_executable(command, data));
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
