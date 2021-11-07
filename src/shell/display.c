/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/07 10:41:50 by efrancon         ###   ########.fr       */
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
		tmp = ft_substr(
				cwd, ft_strlen(get_env("HOME", data->env)), ft_strlen(cwd));
		clean_free(&cwd);
		cwd = ft_strjoin("~", tmp);
		clean_free(&tmp);
	}
	usr = ft_strjoin("\e[92;1m", usr);
	usr = ft_strjoin_and_free(usr, "\e[0m:");
	usr = ft_strjoin_and_free(usr, "\e[34;1m");
	usr = ft_strjoin_and_free(usr, cwd);
	clean_free(&cwd);
	cwd = ft_strjoin_and_free(usr, "\e[0m$ ");
	return (cwd);
}
