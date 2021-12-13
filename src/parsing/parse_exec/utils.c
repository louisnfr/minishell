/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:52:51 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 14:51:04 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_cmd_reparse(char *str, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!str)
		return (NULL);
	str = handle_home_var(str, data);
	str = parse_env_variable(NULL, NULL, str, data);
	if (str && !str_is_equal(str, "\"\"") && !str_is_equal(str, "\'\'"))
	{
		pid_value = safe_itoa(data->pid, data);
		ret_value = safe_itoa(data->ret_value, data);
		str = transform_pid_value(str, pid_value, ret_value, data);
		str = transform_ret_value(str, ret_value, pid_value, data);
		clean_free(&pid_value);
		clean_free(&ret_value);
	}
	return (str);
}

char	*transform_cmd(
	char *str, char *pid_value, char *ret_value, t_data *data)
{
	if (!str)
		return (NULL);
	str = handle_home_var(str, data);
	if (str)
	{
		str = parse_env_variable(ret_value, pid_value, str, data);
		str = transform_pid_value(str, pid_value, ret_value, data);
		str = transform_ret_value(str, ret_value, pid_value, data);
	}
	return (str);
}
