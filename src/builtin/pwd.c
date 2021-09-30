/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:49 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 18:10:03 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_pwd(char **cmd, t_data *data)
{
	char	*pwd;

	(void)cmd;
	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (FAIL);
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (SUCCESS);
}
