/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:43:48 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 16:20:50 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *g_env)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		g_env = g_env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
		tmp = g_env;
	}
	free(g_env);
	g_env = NULL;
}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}
