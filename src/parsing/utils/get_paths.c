/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:42 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/21 11:21:51 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_executable(char *command)
{
	char	*path;
	int		i;
	int		j;

	path = NULL;
	if (!command)
		return (path);
	path = (char *)ft_calloc(1, sizeof(char) * (ft_strlen(command) - 1));
	i = 2;
	j = 0;
	while (command[i])
		path[j++] = command[i++];
	path[j] = '\0';
	return (path);
}

char	*find_cmd_path(char *command, char *path, char **all_paths)
{
	int		i;
	char	*cmd_path;

	i = -1;
	clean_free(&path);
	if (command && command[0] && command[0] == '/')
		return (ft_strdup(command));
	if (command && command[0] && command[0] == '.' && command[1] && command[1] == '/')
		return (get_path_executable(command));
	if (command && (str_is_equal(command, ".") || str_is_equal(command, "..")))
		return (NULL);
	while (all_paths && all_paths[++i])
	{
		cmd_path = ft_strjoin(all_paths[i], command);
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
	all_paths = ft_split(path_variable, ':');
	i = -1;
	while (all_paths[++i])
		all_paths[i] = ft_strjoin_and_free(all_paths[i], "/");
	all_paths[i] = NULL;
	return (all_paths);
}
