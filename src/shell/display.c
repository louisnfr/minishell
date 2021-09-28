/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 15:07:02 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = get_env("USER");
	cwd = getcwd(NULL, 0);
	if (ft_strnstr(cwd, get_env("HOME"), ft_strlen(get_env("HOME"))))
	{
		tmp = ft_substr(cwd, 6 + ft_strlen(usr), ft_strlen(cwd));
		free(cwd);
		cwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	ft_putstr_fd("\e[32;1m", 1);
	ft_putstr_fd(usr, 1);
	ft_putstr_fd("\e[0m:", 1);
	ft_putstr_fd("\e[36;1m", 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("$ \e[0m", 1);
	free(cwd);
}
