/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 15:32:42 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **g_env;

char	*get_env(char *arg)
{
	char	*ret;
	int		i;

	i = 0;
	while (!ft_strnstr(g_env[i], arg, ft_strlen(arg)))
		i++;
	ret = g_env[i] + ft_strlen(arg) + 1;
	return (ret);
}
