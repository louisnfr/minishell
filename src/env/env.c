/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/20 13:26:56 by EugenieFran      ###   ########.fr       */
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

	tmp = get_env("SHLVL", data->env);
	i = (ft_atoi(tmp) + 1);
	tmp = ft_itoa(i);
	set_env("SHLVL", tmp, data->env);
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
	env->value = ft_calloc(1, sizeof(char) + (ft_strlen(new_value) + 1));
	if (!env->value)
		return ;
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

char	**env_to_char(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = ft_calloc(1, sizeof(char *) * (get_env_size(env) + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_calloc(1, sizeof(char)
				* (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
		if (!envp[i])
			return (NULL);
		envp[i] = ft_strjoin_and_free(envp[i], tmp->key);
		envp[i] = ft_strjoin_and_free(envp[i], "=");
		envp[i] = ft_strjoin_and_free(envp[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = 0;
	return (envp);
}
