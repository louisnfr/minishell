/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/18 17:39:27 by lraffin          ###   ########.fr       */
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
	char	*cdpath;
	char	*pwd;
	char	*tmp;

	tmp = NULL;
	oldpwd = getcwd(NULL, 0);
	cdpath = get_env("CDPATH", data);
	if (cmd_list->args && cmd_list->args[1])
	{
		ft_putstr_fd("cd: too many arguments\n", cmd_list->error_output);
		return (FAIL);
	}
	if (!cmd_list->args || !ft_strcmp(cmd_list->args[0], "--"))
	{
		if (chdir(get_env("HOME", data)) < 0)
		{
			ft_putstr_fd("cd: HOME not set\n", cmd_list->error_output);
			return (FAIL);
		}
	}
	else if (!ft_strcmp(cmd_list->args[0], "-"))
	{
		ft_putstr_fd(get_env("OLDPWD", data), cmd_list->output);
		ft_putstr_fd("\n", cmd_list->output);
		if (chdir(get_env("OLDPWD", data)) < 0)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", cmd_list->error_output);
			return (FAIL);
		}
	}
	else
	{
		if (ft_strlen(cdpath) > 0
			&& ft_strcmp(cmd_list->args[0], ".")
			&& ft_strcmp(cmd_list->args[0], ".."))
		{
			if (cdpath[ft_strlen(cdpath) - 1] != '/')
			{
				tmp = ft_strjoin(get_env("CDPATH", data), "/");
				tmp = ft_strjoin(tmp, cmd_list->args[0]);
			}
			else
				tmp = ft_strjoin(get_env("CDPATH", data), cmd_list->args[0]);
			if (chdir(tmp) < 0)
			{
				if (chdir(cmd_list->args[0]) < 0)
					return (cd_error(oldpwd, cmd_list));
			}
			else
			{
				ft_putstr_fd(tmp, cmd_list->output);
				ft_putstr_fd("\n", cmd_list->output);
			}
			free(tmp);
		}
		else
		{
			if (chdir(cmd_list->args[0]) < 0)
				return (cd_error(oldpwd, cmd_list));
		}
	}
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD", oldpwd, data->env);
	set_env("PWD", pwd, data->env);
	set_env("OLDPWD", oldpwd, data->export);
	set_env("PWD", pwd, data->export);
	free(pwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}
