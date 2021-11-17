/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/15 16:10:48 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ch_dir(char *dir, char *error_msg, t_cmd *cmd_list)
{
	if (chdir(dir) < 0)
	{
		if (error_msg)
			return (cd_error_msg(error_msg, cmd_list));
		else
			return (cd_error(cmd_list));
	}
	return (EXIT_SUCCESS);
}

void	update_env_pwd(t_data *data, char *pwd, char *oldpwd)
{
	if (!get_env("PWD", data->env))
	{
		add_var(&data->env, new_var("PWD", pwd, 1));
		add_var(&data->export, new_var("PWD", pwd, 1));
	}
	if (!get_env("OLDPWD", data->env))
	{
		add_var(&data->env, new_var("OLDPWD", oldpwd, 1));
		add_var(&data->export, new_var("OLDPWD", oldpwd, 1));
	}
	set_env("OLDPWD", oldpwd, data->env, data);
	set_env("PWD", pwd, data->env, data);
	set_env("OLDPWD", oldpwd, data->export, data);
	set_env("PWD", pwd, data->export, data);
	free(pwd);
	free(oldpwd);
}

t_bool	try_cdpath(char *cdpath, t_data *data, t_cmd *cmd_list)
{
	char	*tmp;

	tmp = NULL;
	if (cdpath[ft_strlen(cdpath) - 1] != '/')
	{
		tmp = safe_strjoin(get_env("CDPATH", data->env), "/", data);
		tmp = safe_strjoin(tmp, cmd_list->args[0], data);
	}
	else
		tmp = safe_strjoin(
				get_env("CDPATH", data->env), cmd_list->args[0], data);
	if (chdir(tmp) < 0)
	{
		if (chdir(cmd_list->args[0]) < 0)
			return (cd_error(cmd_list));
	}
	else
	{
		ft_putstr_fd(tmp, cmd_list->output);
		ft_putstr_fd("\n", cmd_list->output);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

t_bool	handle_dash(t_data *data, t_cmd *cmd_list)
{
	int	ret;

	if (!get_env("OLDPWD", data->env))
		return (cd_error_msg("cd: OLDPWD not set\n", cmd_list));
	ft_putstr_fd(get_env("OLDPWD", data->env), cmd_list->output);
	ft_putstr_fd("\n", cmd_list->output);
	ret = ch_dir(get_env("OLDPWD", data->env), NULL, cmd_list);
	return (ret);
}

t_bool	exec_cd(t_cmd *cmd_list, t_data *data)
{
	char	*oldpwd;
	char	*cdpath;
	char	*pwd;
	int		ret;

	oldpwd = getcwd(NULL, 0);
	cdpath = get_env("CDPATH", data->env);
	if (cmd_list->args && cmd_list->args[1])
		return (cd_error_msg("cd: too many arguments\n", cmd_list));
	if (!cmd_list->args || !ft_strcmp(cmd_list->args[0], "--"))
		ret = ch_dir(get_env("HOME", data->env), "cd: HOME not set\n", cmd_list);
	else if (!ft_strcmp(cmd_list->args[0], "-"))
		ret = handle_dash(data, cmd_list);
	else
	{
		if (ft_strlen(cdpath) > 0 && ft_strcmp(cmd_list->args[0], ".")
			&& ft_strcmp(cmd_list->args[0], ".."))
			ret = try_cdpath(cdpath, data, cmd_list);
		else
			ret = ch_dir(cmd_list->args[0], NULL, cmd_list);
	}
	pwd = getcwd(NULL, 0);
	if (ret == 0)
		update_env_pwd(data, pwd, oldpwd);
	return (ret);
}
