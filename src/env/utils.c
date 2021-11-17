/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:45:37 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/17 10:17:37 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_data *data)
{
	char	*tmp;
	int		i;

	tmp = get_env("SHLVL", data->env);
	i = (ft_atoi(tmp) + 1);
	tmp = ft_itoa(i);
	set_env("SHLVL", tmp, data->env, data);
	free(tmp);
}

char	*get_env(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(char *key, char *new_value, t_env *env, t_data *data)
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
	env->value = ft_calloc(1, sizeof(char) + (ft_strlen(new_value) + 1));
	if (!env->value)
		exit_error_bool("malloc()", data);
	ft_memcpy(env->value, new_value, ft_strlen(new_value) + 1);
	env = head;
}

int	get_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
