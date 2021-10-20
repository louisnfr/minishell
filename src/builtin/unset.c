/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/20 14:21:30 by efrancon         ###   ########.fr       */
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

t_bool	unset(t_env *env, t_cmd *cmd_list)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = -1;
	while (cmd_list->args[++i])
	{
		if (!get_env(cmd_list->args[i], env))
			return (EXIT_SUCCESS);
		prev = find_prev_var(cmd_list->args[i], env);
		if (!prev)
		{
			tmp = env;
			free(env);
			env = tmp->next;
			return (EXIT_SUCCESS);
		}
		tmp = prev->next->next;
		free(prev->next);
		prev->next = tmp;
	}
	return (EXIT_SUCCESS);
}

t_bool	exec_unset(t_cmd *cmd_list, t_data *data)
{
	if (!cmd_list->args || !cmd_list->args[0])
		return (EXIT_SUCCESS);
	if (cmd_list && cmd_list->next && cmd_list->next->delimiter == PIPE)
		return (EXIT_SUCCESS);
	unset(data->env, cmd_list);
	unset(data->export, cmd_list);
	return (EXIT_SUCCESS);
}
