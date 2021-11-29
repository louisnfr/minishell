/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:36:51 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 23:36:57 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
