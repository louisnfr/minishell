/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:31 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 18:07:35 by lraffin          ###   ########.fr       */
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

t_bool	exec_echo(char **cmd, t_data *data)
{
	int	i;
	int	eol;

	if (!cmd[1])
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
	i = 0;
	eol = 1;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		eol = 0;
		i++;
	}
	while (cmd[++i])
	{
		if (cmd[i][0] == '$' && cmd[i][1])
			print_var(cmd[i] + 1, data);
		else
		{
			ft_putstr(cmd[i]);
			if (cmd[i + 1])
				ft_putchar(32);
		}
	}
	if (eol)
		ft_putchar('\n');
	return (SUCCESS);
}
