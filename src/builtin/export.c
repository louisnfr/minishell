/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/14 17:49:37 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	tmp = data->env;
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
		if (!ft_strnstr(cmd_list->args[i], "=", ft_strlen(cmd_list->args[i])))
		{
			if (ft_str_isdigit(cmd_list->args[i]))
			{
				printf("export: `%s': not a valid identifier\n",
					cmd_list->args[i]);
				ret = EXIT_FAILURE;
			}
			else if (!already_exists(cmd_list->args[i], data))
				add_var(&data->env, new_var(cmd_list->args[i], "\0", 0));
			else
				printf("existe deja\n");
		}
		else
		{
			var = ft_split_on_first(cmd_list->args[i], '=');
			if (ft_str_isdigit(var[0]))
			{
				printf("export: `%s': not a valid identifier\n", var[0]);
				ret = EXIT_FAILURE;
			}
			else if (!already_exists(var[0], data))
				add_var(&data->env, new_var(var[0], var[1], 1));
			else
				printf("existe deja\n");
			free_split(var);
		}
	}
	return (ret);
}
