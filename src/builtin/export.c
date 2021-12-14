/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 13:52:23 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error(t_cmd *cmd_list, int i)
{
	ft_putstr_fd("export: `", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[i], cmd_list->error_output);
	ft_putstr_fd("': not a valid identifier\n", cmd_list->error_output);
	return (EXIT_FAILURE);
}

static t_bool	check_export(char *s, int *append)
{
	int	i;

	if (s && !ft_strlen(s))
		return (FAIL);
	if (ft_isdigit(s[0]) || s[0] == '=')
		return (FAIL);
	i = -1;
	while (s[++i] && s[i] != '=')
	{
		if (i > 0 && s[i] == '+' && s[i + 1] == '=')
		{
			*append = true;
			continue ;
		}
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=')
			return (FAIL);
	}
	return (SUCCESS);
}

static void	export_var(t_data *data, t_cmd *cmd_list, int append, int i)
{
	if (append)
		append_var_env(data, cmd_list, i);
	else
		add_var_env(data, cmd_list, i);
}

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	int		append;
	int		ret;
	int		i;

	append = false;
	ret = EXIT_SUCCESS;
	i = -1;
	if (!cmd_list->args)
		print_export(cmd_list, data);
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (!check_export(cmd_list->args[i], &append))
			ret = export_error(cmd_list, i);
		else if (!ft_strnstr(cmd_list->args[i], "=",
				ft_strlen(cmd_list->args[i])))
		{
			if (!already_exists(cmd_list->args[i], data->export))
				add_var(
					&data->export, new_var(cmd_list->args[i], "\0", 0, data));
		}
		else
			export_var(data, cmd_list, append, i);
	}
	return (ret);
}
