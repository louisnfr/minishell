/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:26:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 10:36:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*secured_init_var_env(
	char *ret_value, char *pid_value, char *str, t_data *data)
{
	t_var	*var;

	var = init_var();
	if (!var)
	{
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		clean_free(&pid_value);
		clean_free(&ret_value);
		exit_error_str(str, "malloc()", data);
	}
	return (var);
}

t_var	*secured_init_var_heredoc(char *str, char *new_str, t_data *data)
{
	t_var	*var;

	var = init_var();
	if (!var)
	{
		if (new_str)
			clean_free(&new_str);
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(str, "malloc()", data);
	}
	return (var);
}

void	re_init_data_var(t_data *data)
{
	data->pid_str = NULL;
	data->ret_str = NULL;
	data->tmp_path = NULL;
	data->tmp_cmd = NULL;
}
