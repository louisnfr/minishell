/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:45:37 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/13 19:48:13 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env)
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

t_bool	already_exists(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	exit_error_env_to_char(char **envp, char **cmd_array, t_data *data)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit_error_child(envp, cmd_array, "malloc()", data);
}

char	**env_to_char(t_env *env, t_data *data, char **cmd_array)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = ft_calloc(1, sizeof(char *) * (get_env_size(env) + 1));
	if (!envp)
		exit_error_env_to_char(envp, cmd_array, data);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_calloc(1, sizeof(char)
				* (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
		if (!envp[i])
			exit_error_env_to_char(envp, cmd_array, data);
		envp[i] = safe_strjoin_and_free(envp[i], tmp->key, data);
		envp[i] = safe_strjoin_and_free(envp[i], "=", data);
		envp[i] = safe_strjoin_and_free(envp[i], tmp->value, data);
		i++;
		tmp = tmp->next;
	}
	envp[i] = 0;
	return (envp);
}
