/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:20:43 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 10:38:06 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_new_input(t_var *var, char *str)
{
	if (!var)
		return (-1);
	if (!str || !str[var->i])
	{
		free_var(var);
		return (FAIL);
	}
	return (SUCCESS);
}

void	exit_error_redirections(char *input, char **argv, t_data *data)
{
	free_double_str(argv);
	exit_error_str(input, "malloc()", data);
}

void	exit_error_files(char **copy_files, char **argv, t_data *data)
{
	free(copy_files);
	copy_files = NULL;
	exit_error_strs(argv, "malloc()", data);
}

void	exit_error_refill(
	char **existing_options, char **strs, t_cmd *cmd_list, t_data *data)
{
	free_double_str(strs);
	free_double_str(data->tmp_args);
	if (cmd_list->path)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit_error_child(existing_options, NULL, "malloc()", data);
	}
	exit_error_strs(existing_options, "malloc()", data);
}

void	exit_error_env_key(char *str, t_var *var, t_data *data)
{
	if (var)
		free(var);
	if (!data->tmp_cmd)
	{
		clean_free(&str);
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
	}
	if (data->pid_str)
		clean_free(data->pid_str);
	if (data->ret_str)
		clean_free(data->ret_str);
	if (data->tmp_path)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit_error_child(NULL, NULL, "malloc()", data);
	}
	exit_error_str(NULL, "malloc()", data);
}
