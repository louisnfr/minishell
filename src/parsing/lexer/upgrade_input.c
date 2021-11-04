/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:47:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:47:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_special_value(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	*pid_value;
	char	*ret_value;

	pid_value = ft_itoa(data->pid);
	ret_value = ft_itoa(data->ret_value);
	cmd_list->command = parse_env_variable(cmd_list->command, data);
	cmd_list->command = transform_pid_value(cmd_list->command, pid_value);
	cmd_list->command = transform_ret_value(cmd_list->command, ret_value);
	i = 0;
	while (cmd_list->args && cmd_list->args[i])
	{
		cmd_list->args[i] = parse_env_variable(cmd_list->args[i], data);
		cmd_list->args[i] = transform_pid_value(cmd_list->args[i], pid_value);
		cmd_list->args[i] = transform_ret_value(cmd_list->args[i], ret_value);
		i++;
	}
	clean_free(&pid_value);
	clean_free(&ret_value);
}
