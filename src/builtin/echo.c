/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:31 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/11 16:00:24 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_echo(t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	eol;

	(void)data;
	if (!cmd_list->args)
	{
		if (!cmd_list->options)
			ft_putchar_fd('\n', cmd_list->output);
		return (EXIT_SUCCESS);
	}
	eol = 1;
	if (cmd_list->options && !ft_strcmp(cmd_list->options[0], "-n"))
		eol = 0;
	i = -1;
	while (cmd_list->args[++i])
	{
		ft_putstr_fd(cmd_list->args[i], cmd_list->output);
		if (cmd_list->args[i + 1])
			ft_putchar_fd(32, cmd_list->output);
	}
	if (eol)
		ft_putchar_fd('\n', cmd_list->output);
	return (EXIT_SUCCESS);
}
