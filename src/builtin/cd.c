/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/15 12:02:13 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	cd_error(char *pwd, t_cmd *cmd_list)
{
	ft_putstr_fd("cd: ", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[0], cmd_list->error_output);
	ft_putstr_fd(": No such file or directory\n", cmd_list->error_output);
	free(pwd);
	return (EXIT_FAILURE);
}

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
	set_env("OLDPWD", oldpwd, data->env);
	set_env("PWD", pwd, data->env);
	set_env("OLDPWD", oldpwd, data->export);
	set_env("PWD", pwd, data->export);
	free(pwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}
