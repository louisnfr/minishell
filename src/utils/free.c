/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:43:48 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/13 18:08:22 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		env = env->next;
		clean_free(&tmp->key);
		clean_free(&tmp->value);
		free(tmp);
		tmp = NULL;
		tmp = env;
	}
	free(env);
	env = NULL;
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
