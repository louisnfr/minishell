/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:28:50 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 12:03:02 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **cmd)
{
	if (is_builtin(cmd[0]))
		exec_builtin(cmd);
	else
	{
		// execve in child
		printf("not builtin cmd\n");
	}
}
