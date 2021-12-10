/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:00:02 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/10 17:23:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_itoa(int n, t_data *data)
{
	char	*new_str;

	new_str = ft_itoa(n);
	if (!new_str)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}

t_bool	safe_unlink(char *pathname, t_data *data)
{
	int	ret;

	ret = unlink(pathname);
	if (ret == -1)
		return (exit_error_bool("unlink()", data));
	return (SUCCESS);
}

t_bool	safe_close_fd(int fd, t_data *data)
{
	int	ret;

	if (fd <= 2)
		return (SUCCESS);
	ret = close(fd);
	if (ret == -1)
		return (exit_error_bool("close()", data));
	return (SUCCESS);
}

char	**safe_double_strdup(char **str, int size, t_data *data)
{
	char	**new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = (char **)ft_calloc(1, sizeof(char *) * (size + 1));
	if (!new_str)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	i = -1;
	while (str && ++i < size)
	{
		if (str[i])
			new_str[i] = safe_strdup(str[i], data);
		else
			new_str[i] = NULL;
	}
	new_str[i] = NULL;
	return (new_str);
}

char	*safe_substr(const char *str, int start, int len, t_data *data)
{
	char	*new_str;

	if (!str || !ft_strlen(str))
		return (NULL);
	new_str = ft_substr(str, start, len);
	if (!new_str)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	return (new_str);
}
