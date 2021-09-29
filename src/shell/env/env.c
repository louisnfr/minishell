/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 23:34:50 by lraffin          ###   ########.fr       */
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
		var = ft_split(envp[i], '=');
		add_var(&g_env, new_var(var[0], var[1]));
		free_split(var);
	}
	// incrementer SHLVL
	return (g_env);
}

// extern char **g_env;

// char	*get_env(char *arg)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (!ft_strnstr(g_env[i], arg, ft_strlen(arg)))
// 		i++;
// 	ret = g_env[i] + ft_strlen(arg) + 1;
// 	return (ret);
// }

// void	set_env(char *var, char *value)
// {
// 	(void)value;
// 	int	i;

// 	i = 0;
// 	while (g_env[i] && !ft_strnstr(g_env[i], var, ft_strlen(var)))
// 		i++;
// }
