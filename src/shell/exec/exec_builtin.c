/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:34:02 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 14:59:27 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "echo"))
		exec_echo(cmd, data);
	else if (!ft_strcmp(cmd[0], "cd"))
		exec_cd(cmd, data);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exec_pwd(cmd, data);
	else if (!ft_strcmp(cmd[0], "env"))
		exec_env(cmd, data);
	else if (!ft_strcmp(cmd[0], "export"))
		printf("export\n");
	else if (!ft_strcmp(cmd[0], "unset"))
		printf("unset\n");
	else if (!ft_strcmp(cmd[0], "exit"))
		exec_exit(cmd, data);
}
