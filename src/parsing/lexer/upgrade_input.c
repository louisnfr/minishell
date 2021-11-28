/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:47:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/28 20:52:24 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*transform_home_var(char *str, char *new_str, char *home)
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

static char	*handle_home_var(char *str, t_data *data)
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
			return (exit_error_void(NULL, "malloc()", data));
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

	if (nb_of_args == new_nb_of_args)
		return ;
	args = safe_double_strdup(cmd_list->args, nb_of_args, data);
	free_double_str(cmd_list->args);
	cmd_list->args = (char **)ft_calloc(
			1, sizeof(char *) * (new_nb_of_args + 1));
	if (!cmd_list->args)
		exit_error_bool("malloc()", data);
	j = 0;
	i = -1;
	while (++i < nb_of_args)
	{
		if (args[i])
			cmd_list->args[j++] = safe_strdup(args[i], data);
	}
	cmd_list->args[j] = NULL;
	free_double_str(args);
}

char	*transform_str(
	char *str, char *pid_value, char *ret_value, t_data *data)
{
	if (!str)
		return (NULL);
	str = handle_home_var(str, data);
	str = parse_env_variable(str, data);
	if (str)
	{
		str = transform_pid_value(str, pid_value, data);
		str = transform_ret_value(str, ret_value, data);
	}
	return (str);
}

void	parse_special_value(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	*pid_value;
	char	*ret_value;
	int		new_nb_of_args;

	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	cmd_list->command = transform_str(
			cmd_list->command, pid_value, ret_value, data);
	i = 0;
	new_nb_of_args = 0;
	while (cmd_list->args && cmd_list->args[i])
	{
		cmd_list->args[i] = transform_str(
				cmd_list->args[i], pid_value, ret_value, data);
		if (cmd_list->args[i])
			new_nb_of_args++;
		i++;
	}
	clean_free(&pid_value);
	clean_free(&ret_value);
	delete_void_args(i, new_nb_of_args, cmd_list, data);
}
