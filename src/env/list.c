/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:56:25 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 14:58:53 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_var(char *key, char *value, int is_value, t_data *data)
{
	t_env	*var;

	(void)data;
	var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = (char *)ft_calloc(1, sizeof(char) + (ft_strlen(key) + 1));
	var->value = (char *)ft_calloc(1, sizeof(char) + (ft_strlen(value) + 1));
	if (!var->key || !var->value)
	{
		free_env(var);
		return (NULL);
	}
	ft_memcpy(var->key, key, ft_strlen(key) + 1);
	ft_memcpy(var->value, value, ft_strlen(value) + 1);
	var->is_value = is_value;
	var->next = NULL;
	return (var);
}

static t_env	*get_last(t_env *g_env)
{
	if (!g_env)
		return (NULL);
	while (g_env->next)
		g_env = g_env->next;
	return (g_env);
}

void	add_var(t_env **g_env, t_env *new_var)
{
	t_env	*last;

	if (!*g_env)
		*g_env = new_var;
	else
	{
		last = get_last(*g_env);
		last->next = new_var;
	}
}

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
