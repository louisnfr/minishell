/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:03:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/22 11:28:35 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_key(int k)
{
	return (k & 0x1f);
}

void	clear_prompt(int cx, int k)
{
	int	i;

	i = -1;
	(void)k;
	while (++i < cx)
		write(1, "\x1b[1D", 4);
	write(1, "\x1b[0K", 4);
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
