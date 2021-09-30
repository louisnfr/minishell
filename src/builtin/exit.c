/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 15:01:02 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char **cmd, t_data *data)
{
	ft_putstr("exit\n");
	free_split(cmd);
	// free data
	free_env(data->env);
	exit(EXIT_SUCCESS);
}
