/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:36:51 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/13 20:19:05 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_getcwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = safe_strdup_free(data->last_cwd, data, &data->sh->ret);
	else
	{
		if (data->last_cwd)
			clean_free(&data->last_cwd);
		data->last_cwd = safe_strdup_free(cwd, data, &data->sh->ret);
	}
	return (cwd);
}

char	**copy_strs_and_free(char **strs, t_data *data, char **free)
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
		exit_error_strs(free, "malloc()", data);
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
		exit_error_str(NULL, "malloc()", data);
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	return (strs_copy);
}
