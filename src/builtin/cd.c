/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 15:00:33 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(char **cmd, t_data *data)
{
	char	*oldpwd;
	char	*pwd;
	char	*p;
	char	*tmp;

	oldpwd = getcwd(NULL, 0);
	if (!cmd[1])
		chdir(getenv("HOME"));
	else if (cmd[1][0] == '~')
	{
		p = ft_substr(cmd[1], 1, ft_strlen(cmd[1]));
		tmp = ft_strjoin(getenv("HOME"), p);
		free(p);
		if (chdir(tmp) < 0)
			return (cd_error(oldpwd, cmd));
		free(tmp);
	}
	else
		if (chdir(cmd[1]) < 0)
			return (cd_error(oldpwd, cmd));
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD", oldpwd, data);
	set_env("PWD", pwd, data);
	free(pwd);
	free(oldpwd);
}
