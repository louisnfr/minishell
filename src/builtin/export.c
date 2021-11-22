/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/22 12:08:03 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(t_cmd *cmd_list, int i)
{
	ft_putstr_fd("export: `", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[i], cmd_list->error_output);
	ft_putstr_fd("': not a valid identifier\n", cmd_list->error_output);
	return (EXIT_FAILURE);
}

t_bool	check_export(char *s)
{
	int	i;

	if (ft_isdigit(s[0]) || s[0] == '=')
		return (FAIL);
	i = -1;
	while (s[++i])
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=')
			return (FAIL);
	return (SUCCESS);
}

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	i = -1;
	if (!cmd_list->args)
		print_export(cmd_list, data);
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (!check_export(cmd_list->args[i]))
			ret = export_error(cmd_list, i);
		else if (!ft_strnstr(cmd_list->args[i], "=",
				ft_strlen(cmd_list->args[i])))
		{
			if (!already_exists(cmd_list->args[i], data->export))
				add_var(&data->export, new_var(cmd_list->args[i], "\0", 0));
		}
		else
			add_var_env(data, cmd_list, i);
	}
	return (ret);
}
