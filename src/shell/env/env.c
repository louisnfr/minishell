/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/15 15:54:37 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char **envp)
{
	t_env	*g_env;
	char	**var;
	int		i;

	g_env = NULL;
	i = -1;
	while (envp[++i])
	{
		var = ft_split_on_first(envp[i], '=');
		add_var(&g_env, new_var(var[0], var[1], 1));
		free_split(var);
	}
	return (g_env);
}

void	update_env(t_data *data)
{
	char	*tmp;
	int		i;

	tmp = get_env("SHLVL", data);
	i = (ft_atoi(tmp) + 1);
	tmp = ft_itoa(i);
	set_env("SHLVL", "3", data->env);
	free(tmp);
}

char	*get_env(char *key, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(char *key, char *new_value, t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			break ;
		env = env->next;
	}
	env->is_value = 1;
	free(env->value);
	env->value = malloc(sizeof(char) + (ft_strlen(new_value) + 1));
	if (!env->value)
		return ;
	ft_memcpy(env->value, new_value, ft_strlen(new_value) + 1);
	env = head;
}
