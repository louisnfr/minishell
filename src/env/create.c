/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:47:13 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 14:56:35 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_data *data, t_env *env)
{
	char	*cwd;
	char	*tmp;
	int		i;

	tmp = get_env("SHLVL", env);
	if (tmp)
	{
		i = (ft_atoi(tmp) + 1);
		tmp = safe_itoa(i, data);
		set_env("SHLVL", tmp, env, data);
		clean_free(&tmp);
	}
	tmp = get_env("SHELL", env);
	if (tmp)
	{
		cwd = getcwd(NULL, 0);
		set_env("SHELL", cwd, env, data);
		clean_free(&cwd);
	}
}

static t_env	*dup_env_export(char **envp, t_data *data)
{
	t_env	*g_env;
	char	**var;
	int		i;

	g_env = NULL;
	i = -1;
	while (envp[++i])
	{
		var = safe_split_on_first(envp[i], '=', data);
		if (!ft_strcmp(var[0], "_"))
		{
			free_split(var);
			continue ;
		}
		add_var(&g_env, new_var(var[0], var[1], 1, data));
		free_split(var);
	}
	return (g_env);
}

static t_env	*dup_env(char **envp, t_data *data)
{
	t_env	*g_env;
	t_env	*nvar;
	char	**var;
	int		i;

	g_env = NULL;
	i = -1;
	while (envp[++i])
	{
		var = safe_split_on_first(envp[i], '=', data);
		nvar = new_var(var[0], var[1], 1, data);
		if (!nvar)
			exit_error_strs(var, "malloc()", data);
		add_var(&g_env, nvar);
		free_split(var);
	}
	return (g_env);
}

void	create_update_env(char **envp, t_data *data)
{
	data->env = dup_env(envp, data);
	data->export = dup_env_export(envp, data);
	update_env(data, data->env);
	update_env(data, data->export);
}
