/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:00:02 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/17 12:00:04 by efrancon         ###   ########.fr       */
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
