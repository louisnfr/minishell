/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:09:05 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/26 17:18:23 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *g_env, t_cmd *cmd_list)
{
	while (g_env)
	{
		ft_putstr_fd(g_env->key, cmd_list->output);
		ft_putchar_fd('=', cmd_list->output);
		ft_putstr_fd(g_env->value, cmd_list->output);
		ft_putchar_fd('\n', cmd_list->output);
		g_env = g_env->next;
	}
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
