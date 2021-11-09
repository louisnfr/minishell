/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:31 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/09 22:06:32 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var(char *key, t_data *data)
{
	if (get_env(key, data->env))
		ft_putstr(get_env(key, data->env));
	else
		return ;
}

t_bool	exec_echo(t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	eol;

	(void)data;
	if (!cmd_list->args)
	{
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
