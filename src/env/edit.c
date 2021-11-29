/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:47:29 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:48:28 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *key, char *new_value, t_env *env, t_data *data)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			break ;
		env = env->next;
	}
	env->is_value = 1;
	free(env->value);
	env->value = ft_calloc(1, sizeof(char) + (ft_strlen(new_value) + 1));
	if (!env->value)
		exit_error_bool("malloc()", data);
	if (new_value)
		ft_memcpy(env->value, new_value, ft_strlen(new_value) + 1);
	env = head;
}
