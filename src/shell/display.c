/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/05 15:15:22 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = getenv("USER");
	cwd = getcwd(NULL, 0);
	if (ft_strnstr(cwd, getenv("HOME"), ft_strlen(getenv("HOME"))))
	{
		tmp = ft_substr(cwd, ft_strlen(getenv("HOME")), ft_strlen(cwd));
		free(cwd);
		cwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	tmp = ft_strjoin("\e[32;1m", usr);
	free(usr);
	usr = ft_strjoin(tmp, "\e[0m:");
	free(tmp);
	tmp = ft_strjoin(usr, "\e[36;1m");
	free(usr);
	usr = ft_strjoin(tmp, cwd);
	free(tmp);
	free(cwd);
	cwd = ft_strjoin(usr, "$ \e[0m");
	free(usr);
	return (cwd);
}

/* "\e[32;1m[usr]\e[0m:\e[36;1m[cwd]$ \e[0m" */
