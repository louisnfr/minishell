/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/15 18:54:51 by lraffin          ###   ########.fr       */
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
