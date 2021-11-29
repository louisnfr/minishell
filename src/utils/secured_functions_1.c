/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:59:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/29 23:15:02 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_strdup(char *str, t_data *data)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}

char	**safe_split_on_first(const char *str, char c, t_data *data)
{
	char	**new_str;

	if (!str)
		return (NULL);
	new_str = ft_split_on_first(str, c);
	if (!new_str)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}

char	**safe_split(const char *str, char c, t_data *data)
{
	char	**new_str;

	if (!str)
		return (NULL);
	new_str = ft_split(str, c);
	if (!new_str)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}

char	*safe_strjoin_and_free(char *s1, char *s2, t_data *data)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	new_str = ft_strjoin_and_free(s1, s2);
	if (!new_str)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}

char	*safe_strjoin(char *s1, char *s2, t_data *data)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	if (!new_str)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}
