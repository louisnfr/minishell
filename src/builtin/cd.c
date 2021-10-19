/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/18 20:06:06 by lraffin          ###   ########.fr       */
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
	if (!get_env("PWD", data))
	{
		add_var(&data->env, new_var("PWD", pwd, 1));
		add_var(&data->export, new_var("PWD", pwd, 1));
	}
	if (!get_env("OLDPWD", data))
	{
		add_var(&data->env, new_var("OLDPWD", oldpwd, 1));
		add_var(&data->export, new_var("OLDPWD", oldpwd, 1));
	}
	set_env("OLDPWD", oldpwd, data->env);
	set_env("PWD", pwd, data->env);
	set_env("OLDPWD", oldpwd, data->export);
	set_env("PWD", pwd, data->export);
	free(pwd);
	free(oldpwd);
}


t_bool	try_cdpath(char *cdpath, t_data *data, t_cmd *cmd_list)
{
	char	*tmp;

	tmp = NULL;
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

	if (!get_env("OLDPWD", data))
		return (cd_error_msg("cd: OLDPWD not set\n", cmd_list));
	ft_putstr_fd(get_env("OLDPWD", data), cmd_list->output);
	ft_putstr_fd("\n", cmd_list->output);
	ret = ch_dir(get_env("OLDPWD", data), NULL, cmd_list);
	return (ret);
}

t_bool	exec_cd(t_cmd *cmd_list, t_data *data)
{
	char	*oldpwd;
	char	*cdpath;
	char	*pwd;
	int		ret;

	oldpwd = getcwd(NULL, 0);
	cdpath = get_env("CDPATH", data);
	if (cmd_list->args && cmd_list->args[1])
		return (cd_error_msg("cd: too many arguments\n", cmd_list));
	if (!cmd_list->args || !ft_strcmp(cmd_list->args[0], "--"))
		ret = ch_dir(get_env("HOME", data), "cd: HOME not set\n", cmd_list);
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
