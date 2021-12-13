/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:52:51 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 17:52:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_home_var_2(
	char *ret_value, char *pid_value, char *str, t_data *data)
{
	char	*new_str;
	char	*home;
	int		total_length;

	new_str = NULL;
	home = NULL;
	if (str_is_equal(str, "~") || (!ft_strncmp("~/", str, 2)
			&& !ft_strncmp(str, "~/", 2)))
	{
		home = get_env("HOME", data->env);
		total_length = ft_strlen(str) + ft_strlen(home);
		new_str = (char *)ft_calloc(1, sizeof(char) * total_length);
		if (!new_str)
		{
			clean_free(&ret_value);
			clean_free(&pid_value);
			if (data->argv && *data->argv)
				free_double_str(*data->argv);
			exit_error_str(str, "malloc()", data);
		}
		new_str = transform_home_var(str, new_str, home);
		return (new_str);
	}
	return (str);
}

char	*transform_cmd_reparse(char *str, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!str)
		return (NULL);
	str = handle_home_var_2(NULL, NULL, str, data);
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
	str = handle_home_var_2(ret_value, pid_value, str, data);
	if (str)
	{
		str = parse_env_variable(ret_value, pid_value, str, data);
		str = transform_pid_value(str, pid_value, ret_value, data);
		str = transform_ret_value(str, ret_value, pid_value, data);
	}
	return (str);
}
