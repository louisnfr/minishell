/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:34:44 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/02 23:49:45 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update(t_data *data, t_confg *sh, char **input, char *before)
{
	*input = ft_calloc(ft_strlen(before), sizeof(char));
	if (!*input)
		exit_error_void(NULL, "malloc()", data);
	ft_strlcpy(*input, before, ft_strlen(before));
	clean_free(&before);
	clear_prompt(sh->cx, 1);
	write(1, *input, ft_strlen(*input));
	sh->cx = ft_strlen(*input);
	sh->cx_max = ft_strlen(*input);
}

static void	update_history(t_data *data, t_confg *sh, t_hist *hist, char *input)
{
	while (hist)
	{
		if (hist->num == sh->search)
			break ;
		hist = hist->next;
	}
	clean_free(&hist->new);
	hist->new = ft_calloc(1, sizeof(char) * (ft_strlen(input)));
	if (!hist->new)
		exit_error_void(NULL, "malloc()", data);
	ft_strlcpy(hist->new, input, ft_strlen(input));
}

static void	update_selected_input(t_data *data, t_confg *sh, char *before)
{
	if (sh->search == sh->h_num)
		update(data, sh, &sh->current, before);
	else
	{
		update(data, sh, &sh->input, before);
		update_history(data, sh, sh->history, sh->input);
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
	update_selected_input(data, sh, before);
}

void	process_tab_key(t_confg *sh, t_data *data)
{
	struct dirent	*entity;
	DIR				*directory;
	char			*current;

	current = get_current_word(sh, data);
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
