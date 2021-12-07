/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:02:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/07 12:09:48 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reparse_command(t_cmd **cmd_list, t_data *data)
{
	char	**strs;
	int		i;

	strs = safe_split((*cmd_list)->command, 32, data);
	clean_free(&(*cmd_list)->command);
	(*cmd_list)->command = safe_strdup(strs[0], data);
	i = 1;
	refill_options(&i, strs, cmd_list, data);
	refill_args(i, strs, cmd_list, data);
	free_double_str(strs);
}

void	recheck_cmd_path(t_cmd **cmd_list, t_data *data)
{
	char	*pid_value;
	char	*ret_value;
	int		ret;

	ret = need_recheck(cmd_list, data);
	if (!ret)
	{
		if ((*cmd_list)->command && cmd_is_builtin((*cmd_list)->command))
			(*cmd_list)->is_builtin = TRUE;
		return ;
	}
	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	(*cmd_list)->command = transform_str(
			(*cmd_list)->command, pid_value, ret_value, data);
	if ((*cmd_list)->command)
	{
		if (ft_strchr((*cmd_list)->command, 32) && ret != 2)
			reparse_command(cmd_list, data);
		(*cmd_list)->path = find_cmd_path(
				(*cmd_list)->command, NULL, data->all_paths, data);
	}
	if (!(*cmd_list)->command || !(*cmd_list)->command[0])
		clean_free(&(*cmd_list)->path);
	clean_free(&pid_value);
	clean_free(&ret_value);
}

char	*transform_str_cmd(
	char *str, char *pid_value, char *ret_value, t_data *data)
{
	if (!str)
		return (NULL);
	str = handle_home_var(str, data);
	if (str)
	{
		str = parse_env_variable(str, data);
		str = transform_pid_value(str, pid_value, data);
		str = transform_ret_value(str, ret_value, data);
	}
	return (str);
}

void	check_expansion_var(char *command, t_data *data)
{
	char	*pid_value;
	char	*ret_value;
	char	*command_tmp;

	command_tmp = safe_strdup(command, data);
	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	command_tmp = transform_str_cmd(
			command_tmp, pid_value, ret_value, data);
	if (!command_tmp)
		data->i++;
	clean_free(&command_tmp);
	clean_free(&pid_value);
	clean_free(&ret_value);
}
