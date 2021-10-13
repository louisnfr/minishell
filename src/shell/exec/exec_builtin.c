/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:34:02 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 11:03:38 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_builtin(t_cmd *cmd_list, t_data *data)
{
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
