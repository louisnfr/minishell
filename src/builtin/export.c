/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/08 18:49:17 by lraffin          ###   ########.fr       */
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

void	print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		ft_putstr("export ");
		ft_putstr(tmp->key);
		if (tmp->value)
		{
			ft_putchar('=');
			ft_putstr(tmp->value);
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	char	**var;
	int		i;

	i = -1;
	if (!cmd_list->args)
		print_export(data);
	while (cmd_list->args && cmd_list->args[++i])
	{
		var = ft_split_on_first(cmd_list->args[i], '=');
		if (!already_exists(var[0], data))
			add_var(&data->env, new_var(var[0], var[1]));
		else
			printf("existe deja\n");
		free_split(var);
	}
	return (EXIT_SUCCESS);
}
