/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:43:27 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/20 16:43:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_oldpwd(char *oldpwd, char *command)
{
	ft_putstr_fd("chdir: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	perror(oldpwd);
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Stale file handle\n", 2);
	return (1);
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

int	get_ret(char *oldpwd, char *cdpath, t_cmd *cmd_list, t_data *data)
{
	int	ret;

	if (!oldpwd && (str_is_equal(cmd_list->args[0], ".")
			|| str_is_equal(cmd_list->args[0], "..")))
		ret = error_oldpwd(oldpwd, cmd_list->args[0]);
	else if (ft_strlen(cdpath) > 0 && ft_strcmp(cmd_list->args[0], ".")
		&& ft_strcmp(cmd_list->args[0], ".."))
		ret = try_cdpath(cdpath, data, cmd_list);
	else
		ret = ch_dir(cmd_list->args[0], NULL, cmd_list);
	return (ret);
}
