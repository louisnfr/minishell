/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/05 14:58:31 by lraffin          ###   ########.fr       */
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
		printf("%s=%s\n", var[0], var[1]);
		add_var(&g_env, new_var(var[0], var[1]));
		free_split(var);
	}
	// print_env(g_env);
	return (g_env);
}

void	update_env(t_data *data)
{
	char	*tmp;
	int		i;

	tmp = get_env("SHLVL", data);
	i = (ft_atoi(tmp) + 1);
	tmp = ft_itoa(i);
	set_env("SHLVL", tmp, data);
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

void	set_env(char *key, char *new_value, t_data *data)
{
	t_env	*head;

	head = data->env;
	while (data->env)
	{
		if (!ft_strcmp(data->env->key, key))
			break ;
		data->env = data->env->next;
	}
	free(data->env->value);
	data->env->value = malloc(sizeof(char) + (ft_strlen(new_value) + 1));
	if (!data->env->value)
		return ;
	ft_memcpy(data->env->value, new_value, ft_strlen(new_value) + 1);
	data->env = head;
}
