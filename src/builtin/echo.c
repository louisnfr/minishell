/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:31 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 13:46:14 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var(char *cmd)
{
	if (get_env(cmd + 1))
		ft_putstr(get_env(cmd + 1));
	else
		return ;
}

void	exec_echo(char **cmd)
{
	int	i;
	int	eol;

	if (!cmd[1])
	{
		ft_putchar('\n');
		return ;
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
			print_var(cmd[i]);
		else
		{
			ft_putstr(cmd[i]);
			if (cmd[i + 1])
				ft_putchar(32);
		}
	}
	if (eol)
		ft_putchar('\n');
}
