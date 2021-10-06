/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/06 15:32:38 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_cd(t_cmd *cmd_list, t_data *data)
{
	char	*oldpwd;
	char	*pwd;
	char	*p;
	char	*tmp;

	oldpwd = getcwd(NULL, 0);
	if (!cmd_list->args)
		chdir(getenv("HOME"));
	else if (cmd_list->args[0][0] == '~')
	{
		p = ft_substr(cmd_list->args[0], 1, ft_strlen(cmd_list->args[0]));
		tmp = ft_strjoin(getenv("HOME"), p);
		free(p);
		if (chdir(tmp) < 0)
			return (cd_error(oldpwd, cmd_list));
		free(tmp);
	}
	else
		if (chdir(cmd_list->args[0]) < 0)
			return (cd_error(oldpwd, cmd_list));
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD", oldpwd, data);
	set_env("PWD", pwd, data);
	free(pwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}
