/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/15 12:23:01 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_digit_error(t_cmd *cmd_list, int i)
{
	ft_putstr_fd("export: `", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[i], cmd_list->error_output);
	ft_putstr_fd("': not a valid identifier\n", cmd_list->error_output);
	return (EXIT_FAILURE);
}

t_bool	already_exists(char *var, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
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

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	char	**var;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	i = -1;
	if (!cmd_list->args)
		print_export(cmd_list, data);
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (ft_isdigit(cmd_list->args[i][0]))
			ret = export_digit_error(cmd_list, i);
		else if (!ft_strnstr(cmd_list->args[i], "=", ft_strlen(cmd_list->args[i])))
			if (!already_exists(cmd_list->args[i], data))
				add_var(&data->export, new_var(cmd_list->args[i], "\0", 0));
		else
		{
			var = ft_split_on_first(cmd_list->args[i], '=');
			if (!already_exists(var[0], data))
			{
				add_var(&data->env, new_var(var[0], var[1], 1));
				add_var(&data->export, new_var(var[0], var[1], 1));
			}
			else
				set_env;
			free_split(var);
		}
	}
	return (ret);
}
