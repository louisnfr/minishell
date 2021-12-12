/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:33:00 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 18:07:59 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	fill_wildcard_arg_builtin(
	char **new_args, int *i, char *wildcard_arg, t_data *data)
{
	DIR				*directory;
	struct dirent	*entity;
	int				i_ref;

	i_ref = *i;
	directory = opendir(".");
	if (!directory)
		return (FAIL);
	entity = readdir(directory);
	while (entity != NULL)
	{
		if (matching_name(entity->d_name, wildcard_arg))
		{
			new_args[*i] = safe_strdup(entity->d_name, data);
			(*i)++;
		}
		entity = readdir(directory);
	}
	closedir(directory);
	if (*i == i_ref)
	{
		new_args[*i] = safe_strdup(wildcard_arg, data);
		(*i)++;
	}
	return (SUCCESS);
}

static t_bool	fill_new_args(int new_length, t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = (char **)ft_calloc(1, sizeof(char *) * (new_length + 1));
	if (!new_args)
		exit_error_str(NULL, "malloc()", data);
	i = -1;
	j = 0;
	while (cmd_list->args[++i])
	{
		if (ft_strchr(cmd_list->args[i], '*'))
			fill_wildcard_arg_builtin(
				&(*new_args), &j, cmd_list->args[i], data);
		else
			new_args[j++] = cmd_list->args[i];
	}
	new_args[j] = NULL;
	free_double_str(cmd_list->args);
	cmd_list->args = new_args;
	return (SUCCESS);
}

static t_bool	parse_wildcard_args(t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		new_length;
	int		ret;

	if (!cmd_list->args)
		return (SUCCESS);
	new_length = 0;
	ret = 0;
	i = -1;
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (ft_strchr(cmd_list->args[i], '*'))
			ret += count_wildcard_arg(&new_length, cmd_list->args[i]);
		else
			new_length++;
	}
	if (ret == 0)
		return (SUCCESS);
	fill_new_args(new_length, cmd_list, data);
	return (SUCCESS);
}

t_bool	exec_builtin(t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_op	*builtins[8];

	builtins[0] = exec_echo;
	builtins[1] = exec_cd;
	builtins[2] = exec_pwd;
	builtins[3] = exec_env;
	builtins[4] = exec_history;
	builtins[5] = exec_export;
	builtins[6] = exec_unset;
	builtins[7] = exec_exit;
	parse_special_value(cmd_list, data);
	parse_wildcard_args(cmd_list, data);
	if (cmd_list->input == -1 || cmd_list->output == -1)
		return (EXIT_FAILURE);
	i = -1;
	while (data->builtins[++i])
	{
		if (str_is_equal(cmd_list->command, data->builtins[i]))
			break ;
	}
	return (builtins[i](cmd_list, data));
}
