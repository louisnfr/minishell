/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:34:44 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/26 01:15:24 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(int c)
{
	return (c == ' ' || c == '/' || c == ';');
}

int	get_cut_pos(t_config *sh)
{
	int		i;

	i = sh->cx - 1;
	while (i && !is_sep(sh->current[i - 1]))
		i--;
	return (i);
}

char	*get_current_word(t_config *sh)
{
	char	*substr;
	int		i;

	i = sh->cx - 1;
	// printf("check -%c-\n", sh->current[sh->cx-1]);
	while (i && !is_sep(sh->current[i - 1]))
		i--;
	substr = ft_substr(sh->current, i, sh->cx - i);
	return (substr);
}

void	edit_input(t_config *sh, char *entity)
{
	char	*before;
	char	*after;
	int		i;

	i = get_cut_pos(sh);
	after = ft_substr(sh->current, sh->cx, ft_strlen(sh->current));
	before = ft_substr(sh->current, 0, i);
	before = ft_strjoin_and_free(before, entity);
	before = ft_strjoin_and_free(before, after);
	clean_free(&after);
	before = ft_strjoin_and_free(before, "  ");
	clean_free(&sh->current);
	sh->current = ft_calloc(ft_strlen(before), sizeof(char));
	ft_strlcpy(sh->current, before, ft_strlen(before));
	clean_free(&before);
	clear_prompt(sh->cx, 1);
}

void	process_tab_key(t_config *sh)
{
	struct dirent	*entity;
	DIR				*directory;
	char			*current;

	current = get_current_word(sh);
	// printf("current : -%s-\n", current);
	if (sh->current)
	{
		directory = opendir(".");
		entity = readdir(directory);
		closedir(directory);
		while (entity != NULL)
		{
			if (ft_strnstr(entity->d_name, current, ft_strlen(current)))
				break ;
			entity = readdir(directory);
		}
		if (!entity)
			return ;
		edit_input(sh, entity->d_name);
		write(1, sh->current, ft_strlen(sh->current));
		sh->cx = ft_strlen(sh->current);
		sh->cx_max = ft_strlen(sh->current);
	}
}
