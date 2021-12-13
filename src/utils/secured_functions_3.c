/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_functions_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:50:07 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:50:09 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
