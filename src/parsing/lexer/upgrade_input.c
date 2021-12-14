/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:47:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 12:35:00 by efrancon         ###   ########.fr       */
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
			while (home && home[k])
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
			return (NULL);
		new_str = transform_home_var(str, new_str, home);
		return (new_str);
	}
	return (str);
}

static void	delete_void_args(
	int nb_of_args, int new_nb_of_args, t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		j;
	char	**args;

	if (!cmd_list->args || nb_of_args == new_nb_of_args)
		return ;
	if (!new_nb_of_args)
		return (clean_free_double_str(nb_of_args, &cmd_list));
	args = safe_double_strdup(cmd_list->args, nb_of_args, cmd_list, data);
	clean_free_double_str(nb_of_args, &cmd_list);
	cmd_list->args = (char **)ft_calloc(
			1, sizeof(char *) * (new_nb_of_args + 1));
	if (!cmd_list->args)
		exit_error_args(nb_of_args, args, cmd_list, data);
	j = 0;
	i = -1;
	while (++i < nb_of_args)
	{
		if (args[i])
			cmd_list->args[j++] = safe_strdup(args[i], data);
	}
	cmd_list->args[j] = NULL;
	free_args(nb_of_args, args);
}

char	*transform_str(char *str, t_cmd *cmd_list, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!str)
		return (NULL);
	str = handle_home_var(str, data);
	if (!str)
		exit_error_home(NULL, NULL, cmd_list, data);
	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	data->pid_str = &pid_value;
	data->ret_str = &ret_value;
	data->tmp_path = cmd_list->path;
	data->tmp_cmd = cmd_list->command;
	str = parse_env_variable(ret_value, pid_value, str, data);
	if (str)
	{
		str = transform_pid_value(str, pid_value, ret_value, data);
		str = transform_ret_value(str, ret_value, pid_value, data);
	}
	clean_free(&pid_value);
	clean_free(&ret_value);
	re_init_data_var(data);
	return (str);
}

void	parse_special_value(t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	new_nb_of_args;

	data->to_reparse = FALSE;
	cmd_list->command = transform_str(cmd_list->command, cmd_list, data);
	i = 0;
	new_nb_of_args = 0;
	while (cmd_list->args && cmd_list->args[i])
	{
		if (ft_strchr(cmd_list->args[i], '$'))
			data->to_reparse = TRUE;
		cmd_list->args[i] = transform_str(cmd_list->args[i], cmd_list, data);
		if (cmd_list->args[i])
			new_nb_of_args++;
		i++;
	}
	delete_void_args(i, new_nb_of_args, cmd_list, data);
	if (data->to_reparse)
		check_options_in_args(cmd_list, data);
}
