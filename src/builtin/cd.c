/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 13:52:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_data *data, char *pwd, char *oldpwd)
{
	if (!get_env("OLDPWD", data->env))
	{
		add_var(&data->env, new_var("OLDPWD", oldpwd, 1, data));
		add_var(&data->export, new_var("OLDPWD", oldpwd, 1, data));
	}
	if (oldpwd)
	{
		set_env("OLDPWD", oldpwd, data->env, data);
		set_env("OLDPWD", oldpwd, data->export, data);
	}
	if (get_env("PWD", data->env) && pwd)
	{
		set_env("PWD", pwd, data->env, data);
		set_env("PWD", pwd, data->export, data);
	}
}

static t_bool	handle_dash(t_data *data, t_cmd *cmd_list)
{
	int	ret;

	if (!get_env("OLDPWD", data->env))
		return (cd_error_msg("cd: OLDPWD not set\n", cmd_list));
	ft_putstr_fd(get_env("OLDPWD", data->env), cmd_list->output);
	ft_putstr_fd("\n", cmd_list->output);
	ret = ch_dir(get_env("OLDPWD", data->env), NULL, cmd_list);
	return (ret);
}

t_bool	ch_dir(char *dir, char *error_msg, t_cmd *cmd_list)
{
	int	ret;

	ret = -1;
	if (dir)
	{
		if (!ft_strlen(dir))
			return (EXIT_SUCCESS);
		ret = chdir(dir);
	}
	if (ret < 0)
	{
		if (error_msg)
			return (cd_error_msg(error_msg, cmd_list));
		else
			return (cd_error(cmd_list));
	}
	return (EXIT_SUCCESS);
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
	{
		clean_free(&oldpwd);
		return (cd_error_msg("cd: too many arguments\n", cmd_list));
	}
	if (!cmd_list->args || !cmd_list->args[0] || (cmd_list->args
			&& !ft_strcmp(cmd_list->args[0], "--")))
		ret = ch_dir(get_env("HOME", data->env), "cd: HOME not set\n", cmd_list);
	else if (cmd_list->args && !ft_strcmp(cmd_list->args[0], "-"))
		ret = handle_dash(data, cmd_list);
	else
		ret = get_ret(oldpwd, cdpath, cmd_list, data);
	pwd = getcwd(NULL, 0);
	if (ret == 0)
		update_env_pwd(data, pwd, oldpwd);
	clean_free(&pwd);
	clean_free(&oldpwd);
	return (ret);
}
