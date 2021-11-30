/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:47:13 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/30 11:46:22 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_data *data, t_env *env)
{
	char	*tmp;
	int		i;

	tmp = get_env("SHLVL", env);
	i = (ft_atoi(tmp) + 1);
	tmp = safe_itoa(i, data);
	set_env("SHLVL", tmp, env, data);
	free(tmp);
}

static t_env	*dup_env(char **envp, t_data *data)
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
