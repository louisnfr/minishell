/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:56:25 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/19 15:12:23 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_var(char *key, char *value, int is_value)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = malloc(sizeof(char) + (ft_strlen(key) + 1));
	var->value = malloc(sizeof(char) + (ft_strlen(value) + 1));
	if (!var->key || !var->value)
		return (NULL);
	ft_memcpy(var->key, key, ft_strlen(key) + 1);
	ft_memcpy(var->value, value, ft_strlen(value) + 1);
	var->is_value = is_value;
	var->next = NULL;
	return (var);
}

t_env	*get_last(t_env *g_env)
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
