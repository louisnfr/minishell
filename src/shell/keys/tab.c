/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:34:44 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 21:26:30 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_tab_key(t_config *sh)
{
	struct dirent	*entity;
	DIR				*directory;

	if (sh->current)
	{
		directory = opendir(".");
		entity = readdir(directory);
		while (entity != NULL)
		{
			if (ft_strnstr(entity->d_name, sh->current, ft_strlen(sh->current)))
				break ;
			entity = readdir(directory);
		}
		sh->current = realloc(sh->current, ft_strlen(entity->d_name));
		ft_strcpy(sh->current, entity->d_name);
		clear_prompt(sh->cx, 1);
		write(1, sh->current, ft_strlen(sh->current));
		sh->cx = ft_strlen(sh->current);
		sh->cx_max = ft_strlen(sh->current);
		closedir(directory);
	}
}
