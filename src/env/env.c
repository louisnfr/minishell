/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/22 12:06:36 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env(char **envp, t_data *data)
{
	t_env	*g_env;
	char	**var;
	int		i;

	g_env = NULL;
	i = -1;
	while (envp[++i])
	{
		var = safe_split_on_first(envp[i], '=', data);
		add_var(&g_env, new_var(var[0], var[1], 1));
		free_split(var);
	}
	return (g_env);
}

void	create_update_env(char **envp, t_data *data)
{
	data->env = dup_env(envp, data);
	data->export = dup_env(envp, data);
	update_env(data, data->env);
	update_env(data, data->export);
}

char	**env_to_char(t_env *env, t_data *data)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = ft_calloc(1, sizeof(char *) * (get_env_size(env) + 1));
	if (!envp)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_calloc(1, sizeof(char)
				* (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
		if (!envp[i])
			return ((char **)exit_error_void(NULL, "malloc()", data));
		envp[i] = safe_strjoin_and_free(envp[i], tmp->key, data);
		envp[i] = safe_strjoin_and_free(envp[i], "=", data);
		envp[i] = safe_strjoin_and_free(envp[i], tmp->value, data);
		i++;
		tmp = tmp->next;
	}
	envp[i] = 0;
	return (envp);
}

void	add_var_env(t_data *data, t_cmd *cmd_list, int i)
{
	char	**var;

	var = safe_split_on_first(cmd_list->args[i], '=', data);
	if (!already_exists(var[0], data->env))
		add_var(&data->env, new_var(var[0], var[1], 1));
	else
		set_env(var[0], var[1], data->env, data);
	if (!already_exists(var[0], data->export))
		add_var(&data->export, new_var(var[0], var[1], 1));
	else
		set_env(var[0], var[1], data->export, data);
	free_split(var);
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
