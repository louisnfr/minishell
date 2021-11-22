/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/22 11:34:16 by lraffin          ###   ########.fr       */
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
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (FAIL);
	return (SUCCESS);
}

void	print_export(t_cmd *cmd_list, t_data *data)
{
	t_env	*tmp;

	tmp = data->export;
	while (tmp)
	{
		ft_putstr_fd("export ", cmd_list->output);
		ft_putstr_fd(tmp->key, cmd_list->output);
		if (tmp->is_value)
		{
			ft_putchar_fd('=', cmd_list->output);
			ft_putchar_fd('"', cmd_list->output);
			ft_putstr_fd(tmp->value, cmd_list->output);
			ft_putchar_fd('"', cmd_list->output);
		}
		ft_putchar_fd('\n', cmd_list->output);
		tmp = tmp->next;
	}
}

void	add_var_env(t_data *data, t_cmd *cmd_list, int i)
{
	char	**var;

	var = safe_split_on_first(cmd_list->args[i], '=', data);
	if (!already_exists(var[0], data->env))
		add_var(&data->env, new_var(var[0], var[1], 1));
	else
		set_env(var[0], var[1], data->env, data);
	if (!already_exists(var[0], data->export))
		add_var(&data->export, new_var(var[0], var[1], 1));
	else
		set_env(var[0], var[1], data->export, data);
	free_split(var);
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
