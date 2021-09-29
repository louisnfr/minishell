/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 00:33:00 by lraffin          ###   ########.fr       */
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
		var = ft_split(envp[i], '='); // mauvais split pour LS_COLORS
		add_var(&g_env, new_var(var[0], var[1]));
		free_split(var);
	}
	// add_var(&g_env, new_var("OLDPWD", getcwd(NULL, 0)));
	// incrementer SHLVL
	return (g_env);
}

char	*get_env(char *key)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(char *key, char *new_value)
{
	t_env	*head;

	head = g_env;
	while (g_env)
	{
		if (!ft_strcmp(g_env->key, key))
			break ;
		g_env = g_env->next;
	}
	free(g_env->value);
	g_env->value = malloc(sizeof(char) + (ft_strlen(new_value) + 1));
	if (!g_env->value)
		return ;
	ft_memcpy(g_env->value, new_value, ft_strlen(new_value) + 1);
	g_env = head;
}
