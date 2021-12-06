/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:36:51 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/06 02:18:38 by lraffin          ###   ########.fr       */
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
		return ((char **)exit_error_void(NULL, "malloc()", data));
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	free_double_str(strs);
	return (strs_copy);
}

int	count_slash(char *cwd, int *slash_count)
{
	int	i;

	i = ft_strlen(cwd);
	while (i >= 0 && *slash_count < 3)
	{
		if (cwd[i] == '/')
			(*slash_count)++;
		i--;
	}
	return (i);
}

int	check_gnl(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		printf("check\n");
		if (!str[i] || !ft_isprint(str[i]))
			return (0);
	}
	return (1);
}

int	ctrl_key(int k)
{
	return (k & 0x1f);
}
