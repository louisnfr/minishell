/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:13:56 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 13:13:45 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **g_env;

char	*get_env(char *arg)
{
	char	*ret;
	int		i;

	i = 0;
	while (g_env[i] && !ft_strnstr(g_env[i], arg, ft_strlen(arg)))
		i++;
	if (!g_env[i])
		return (NULL);
	ret = g_env[i] + ft_strlen(arg) + 1;
	return (ret);
}
