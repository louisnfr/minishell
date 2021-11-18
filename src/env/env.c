/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/19 00:31:37 by lraffin          ###   ########.fr       */
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
	if (!envp[0])
		new_env(data);
	else
	{
		data->env = dup_env(envp, data);
		data->export = dup_env(envp, data);
		update_env(data, data->env);
		update_env(data, data->export);
	}
}

void	new_env(t_data *data)
{
	(void)data;
	add_var(&data->export, new_var("OLDPWD", "", 0));
	add_var(&data->env, new_var("PWD", getcwd(NULL, 0), 1));
	add_var(&data->export, new_var("PWD", getcwd(NULL, 0), 1));
	add_var(&data->env, new_var("SHLVL", "1", 1));
	add_var(&data->export, new_var("SHLVL", "1", 1));
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
