/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:33:00 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:35:05 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	fill_wildcard_arg_builtin(char **new_args, int *i, char *wildcard_arg)
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
			new_args[*i] = ft_strdup(entity->d_name);
			(*i)++;
		}
		entity = readdir(directory);
	}
	closedir(directory);
	if (*i == i_ref)
	{
		new_args[*i] = ft_strdup(wildcard_arg);
		(*i)++;
	}
	return (SUCCESS);
}

t_bool	fill_new_args(int new_length, t_cmd *cmd_list)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = (char **)ft_calloc(1, sizeof(char *) * (new_length + 1));
	if (!new_length)
		return (FAIL);
	i = -1;
	j = 0;
	while (cmd_list->args[++i])
	{
		if (ft_strchr(cmd_list->args[i], '*'))
			fill_wildcard_arg_builtin(&(*new_args), &j, cmd_list->args[i]);
		else
			new_args[j++] = cmd_list->args[i];
	}
	new_args[j] = NULL;
	free_double_str(cmd_list->args);
	cmd_list->args = new_args;
	return (SUCCESS);
}

t_bool	parse_wildcard_args(t_cmd *cmd_list)
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
	fill_new_args(new_length, cmd_list);
	return (SUCCESS);
}

t_bool	exec_builtin(t_cmd *cmd_list, t_data *data)
{
	parse_special_value(cmd_list, data);
	parse_wildcard_args(cmd_list);
	if (cmd_list->input == -1 || cmd_list->output == -1)
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd_list->command, "echo"))
		return (exec_echo(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "cd"))
		return (exec_cd(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "pwd"))
		return (exec_pwd(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "env"))
		return (exec_env(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "history"))
		return (exec_history(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "export"))
		return (exec_export(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "unset"))
		return (exec_unset(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "exit"))
		exec_exit(cmd_list, data);
	return (EXIT_FAILURE);
}
