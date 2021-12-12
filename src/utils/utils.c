/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:36:51 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/12 20:02:01 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_getcwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = safe_strdup(data->last_cwd, data);
	else
	{
		if (data->last_cwd)
			clean_free(&data->last_cwd);
		data->last_cwd = safe_strdup(cwd, data);
	}
	return (cwd);
}

char	**copy_strs_and_free(char **strs, t_data *data)
{
	int		i;
	char	**strs_copy;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		i++;
	strs_copy = (char **)ft_calloc(1, sizeof(char *) * (i + 1));
	if (!strs_copy)
		exit_error_str(NULL, "malloc()", data); // leaks non verifie
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	free_double_str(strs);
	return (strs_copy);
}

char	**copy_strs(char **strs, t_data *data)
{
	int		i;
	char	**strs_copy;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		i++;
	if (i < 1)
	{
		free(strs);
		strs = NULL;
		return (NULL);
	}
	strs_copy = (char **)ft_calloc(1, sizeof(char *) * (i + 1));
	if (!strs_copy)
		exit_error_str(NULL, "malloc()", data); // leaks non verifie
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	return (strs_copy);
}
