/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:34:02 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 18:48:23 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_builtin(t_cmd *cmd_list, t_data *data)
{
	if (!ft_strcmp(cmd_list->command, "echo"))
		return(exec_echo(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "cd"))
		return(exec_cd(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "pwd"))
		return(exec_pwd(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "env"))
		return(exec_env(cmd_list, data));
	else if (!ft_strcmp(cmd_list->command, "export"))
		printf("export\n");
	else if (!ft_strcmp(cmd_list->command, "unset"))
		printf("unset\n");
	else if (!ft_strcmp(cmd_list->command, "exit"))
		exec_exit(cmd_list, data);
	return (EXIT_FAILURE);
}
