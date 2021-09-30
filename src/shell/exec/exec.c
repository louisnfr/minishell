/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 14:54:41 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **cmd, t_data *data)
{
	if (!cmd[0])
		return ;
	else if (cmd_is_builtin(cmd[0]))
		exec_builtin(cmd, data);
	else
		printf("not builtin cmd\n");
}
