/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/19 14:28:49 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_prev_var(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool	exec_unset(t_cmd *cmd_list, t_data *data)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = -1;
	while (cmd_list->args[++i])
	{
		if (!get_env(cmd_list->args[i], data))
			return (EXIT_SUCCESS);
		prev = find_prev_var(cmd_list->args[i], data->env);
		if (!prev)
		{
			tmp = data->env;
			free(data->env);
			data->env = tmp->next;
			return (EXIT_SUCCESS);
		}
		tmp = prev->next->next;
		free(prev->next);
		prev->next = tmp;
	}
	return (EXIT_SUCCESS);
}
