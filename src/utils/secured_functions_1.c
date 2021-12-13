/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:59:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:48:33 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_strdup_free(char *str, t_data *data, char **strs)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
	{
		if (strs && strs[0])
			free_double_str(strs);
		else if (strs)
			free(strs);
		exit_error_str(NULL, "malloc()", data);
	}
	return (new_str);
}

char	*safe_strdup(char *str, t_data *data)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		exit_error_str(str, "malloc()", data);
	return (new_str);
}

char	**safe_split_on_first(char *str, char c, t_data *data)
{
	char	**new_str;

	if (!str)
		return (NULL);
	new_str = ft_split_on_first(str, c);
	if (!new_str)
		exit_error_strs(NULL, "malloc()", data);
	return (new_str);
}

char	**safe_split(const char *str, char c, t_data *data)
{
	char	**new_str;

	if (!str)
		return (NULL);
	new_str = ft_split(str, c);
	if (!new_str)
		exit_error_strs(NULL, "malloc()", data);
	return (new_str);
}

char	*safe_strjoin_and_free2(char *s1, char *s2, t_data *data, char **strs)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	new_str = ft_strjoin_and_free(s1, s2);
	if (!new_str)
	{
		if (strs && strs[0])
			free_double_str(strs);
		else if (strs)
			free(strs);
		exit_error_str(NULL, "malloc()", data); // leaks 1 free en trop
	}
	return (new_str);
}

char	*safe_strjoin_and_free(char *s1, char *s2, t_data *data)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	new_str = ft_strjoin_and_free(s1, s2);
	if (!new_str)
	{
		clean_free(&data->sh->ret);
		exit_error_str(NULL, "malloc()", data);
	}
	return (new_str);
}

char	*safe_strjoin(char *s1, char *s2, t_data *data)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	if (!new_str)
	{
		clean_free(&s2);
		clean_free(&data->sh->ret);
		exit_error_str(NULL, "malloc()", data);
	}
	return (new_str);
}
