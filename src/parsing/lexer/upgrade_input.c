/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:47:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 16:22:50 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_home_var(char *str, char *new_str, char *home)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '~')
		{
			i++;
			k = 0;
			while (home[k])
				new_str[j++] = home[k++];
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	clean_free(&str);
	return (new_str);
}

char	*handle_home_var(char *str, t_data *data)
{
	char	*new_str;
	char	*home;

	new_str = NULL;
	home = NULL;
	if (str_is_equal(str, "~") || (!ft_strncmp("~/", str, 2)
		&& !ft_strncmp(str, "~/", 2)))
	{
		home =  get_env("HOME", data->env);
		new_str = (char *)ft_calloc(1, sizeof(char) * (ft_strlen(str) + ft_strlen(home)));
		if (!new_str)
			return (exit_error_void(NULL, "malloc()", data));
		new_str = transform_home_var(str, new_str, home);
		return (new_str);
	}
	return (str);
}

void	parse_special_value(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	*pid_value;
	char	*ret_value;

	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	cmd_list->command = handle_home_var(cmd_list->command, data);
	cmd_list->command = parse_env_variable(cmd_list->command, data);
	cmd_list->command = transform_pid_value(cmd_list->command, pid_value, data);
	cmd_list->command = transform_ret_value(cmd_list->command, ret_value, data);
	i = 0;
	while (cmd_list->args && cmd_list->args[i])
	{
		cmd_list->args[i] = handle_home_var(cmd_list->args[i], data);
		cmd_list->args[i] = parse_env_variable(cmd_list->args[i], data);
		cmd_list->args[i] = transform_pid_value(
				cmd_list->args[i], pid_value, data);
		cmd_list->args[i] = transform_ret_value(
				cmd_list->args[i], ret_value, data);
		i++;
	}
	clean_free(&pid_value);
	clean_free(&ret_value);
}
