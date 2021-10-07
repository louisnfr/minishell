/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:42 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 17:39:43 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd_path(char *command, char **all_paths)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (all_paths[++i])
	{
		cmd_path = ft_strjoin(all_paths[i], command);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		clean_free(&cmd_path);
	}
	return (NULL);
}

char	*get_path_variable(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (envp[i] + 5);
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path_variable;
	char	**all_paths;

	path_variable = get_path_variable(envp);
	if (!path_variable)
		return (NULL);
	all_paths = ft_split(path_variable, ':');
	i = -1;
	while (all_paths[++i])
		all_paths[i] = ft_strjoin_and_free(all_paths[i], "/");
	all_paths[i] = NULL;
	return (all_paths);
}
