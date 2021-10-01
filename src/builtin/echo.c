/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:31 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 18:49:07 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var(char *key, t_data *data)
{
	if (get_env(key, data))
		ft_putstr(get_env(key, data));
	else
		return ;
}

t_bool	exec_echo(t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	eol;

	if (!cmd_list->args)
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
	i = -1;
	eol = 1;
	if (!ft_strcmp(cmd_list->args[0], "-n"))
	{
		eol = 0;
		i++;
	}
	while (cmd_list->args[++i])
	{
		if (cmd_list->args[i][0] == '$' && cmd_list->args[i][1])
			print_var(cmd_list->args[i] + 1, data);
		else
		{
			ft_putstr(cmd_list->args[i]);
			if (cmd_list->args[i + 1])
				ft_putchar(32);
		}
	}
	if (eol)
		ft_putchar('\n');
	return (SUCCESS);
}
