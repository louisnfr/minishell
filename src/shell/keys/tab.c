/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:34:44 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/30 17:40:13 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cut_pos(t_confg *sh)
{
	char	*input;
	int		i;

	input = selected_input(sh);
	i = sh->cx - 1;
	while (i && !is_sep(input[i - 1]))
		i--;
	return (i);
}

static char	*get_current_word(t_confg *sh, t_data *data)
{
	char	*input;
	char	*substr;
	int		i;

	input = selected_input(sh);
	i = sh->cx - 1;
	while (i > 0 && !is_sep(input[i - 1]))
		i--;
	substr = safe_substr(input, i, sh->cx - i, data);
	return (substr);
}

static void	update_selected_input(t_confg *sh, char *before)
{
	if (sh->search == sh->h_num)
	{
		sh->current = ft_calloc(ft_strlen(before), sizeof(char));
		if (!sh->current)
			return (exit_error("malloc()", sh));
		ft_strlcpy(sh->current, before, ft_strlen(before));
		clean_free(&before);
		clear_prompt(sh->cx, 1);
		write(1, sh->current, ft_strlen(sh->current));
		sh->cx = ft_strlen(sh->current);
		sh->cx_max = ft_strlen(sh->current);
	}
	else
	{
		sh->input = ft_calloc(ft_strlen(before), sizeof(char));
		if (!sh->input)
			return (exit_error("malloc()", sh));
		ft_strlcpy(sh->input, before, ft_strlen(before));
		clean_free(&before);
		clear_prompt(sh->cx, 1);
		write(1, sh->input, ft_strlen(sh->input));
		sh->cx = ft_strlen(sh->input);
		sh->cx_max = ft_strlen(sh->input);
	}
}

static void	edit_input(t_confg *sh, char *entity, t_data *data)
{
	char	*input;
	char	*before;
	char	*after;
	int		i;

	i = get_cut_pos(sh);
	input = selected_input(sh);
	after = safe_substr(input, sh->cx, ft_strlen(input), data);
	before = safe_substr(input, 0, i, data);
	before = safe_strjoin_and_free(before, entity, data);
	before = safe_strjoin_and_free(before, after, data);
	clean_free(&after);
	before = safe_strjoin_and_free(before, "  ", data);
	clean_free(&input);
	update_selected_input(sh, before);
}

void	process_tab_key(t_confg *sh, t_data *data)
{
	struct dirent	*entity;
	DIR				*directory;
	char			*current;

	current = get_current_word(sh, data);
	// printf("current : -%s-\n", current);
	if (current)
	{
		directory = opendir(".");
		entity = readdir(directory);
		while (entity != NULL)
		{
			if (ft_strnstr(entity->d_name, current, ft_strlen(current)))
				break ;
			entity = readdir(directory);
		}
		free(current);
		if (!entity)
		{
			closedir(directory);
			return ;
		}
		edit_input(sh, entity->d_name, data);
		closedir(directory);
	}
}
