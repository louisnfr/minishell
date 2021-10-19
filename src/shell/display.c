/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/19 20:04:12 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_data *data)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = get_env("USER", data->env);
	cwd = getcwd(NULL, 0);
	if (ft_strnstr(cwd, get_env("HOME", data->env),
		ft_strlen(get_env("HOME", data->env))))
	{
		tmp = ft_substr(cwd, ft_strlen(get_env("HOME", data->env)), ft_strlen(cwd));
		free(cwd);
		cwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	usr = ft_strjoin("\e[92;1m", usr);
	usr = ft_strjoin(usr, "\e[0m:");
	usr = ft_strjoin(usr, "\e[34;1m");
	usr = ft_strjoin(usr, cwd);
	cwd = ft_strjoin(usr, "\e[0m$ ");
	return (cwd);
}

/* "\e[32;1m[usr]\e[0m:\e[36;1m[cwd]$ \e[0m" */
