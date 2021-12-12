/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:49:39 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 21:42:02 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_delimiters(int i, char **str, char **strs, t_data *data)
{
	int		j;

	if (!malloc_strs(i, str, strs, data))
		exit_error_split(strs, data);
	j = 0;
	if (**str == '(' || **str == ')')
	{
		strs[i][j++] = **str;
		(*str)++;
	}
	else
	{
		while (**str && is_delimiter_split(**str))
		{
			strs[i][j++] = **str;
			(*str)++;
			if (**str == '(' || **str == ')')
				break ;
		}
	}
	strs[i][j] = '\0';
	return (1);
}

static int	get_count(char **str, t_data *data)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = safe_strdup(*str, data);
	while (tmp && tmp[j] && !is_charset_split(tmp[j]))
	{
		if (tmp[j] && (tmp[j] == '\'' || tmp[j] == '\"'))
			count_in_quotes_split(&j, tmp);
		else
			j++;
	}
	clean_free(&tmp);
	return (j);
}

static t_bool	fill_words(int i, char **str, char **strs, t_data *data)
{
	int	j;

	strs[i] = (char *)ft_calloc(1, sizeof(char) * (get_count(str, data) + 1));
	if (!strs[i])
		exit_error_split(strs, data);
	j = 0;
	while (**str && !is_charset_split(**str))
	{
		if (**str && (**str == '\'' || **str == '\"'))
			fill_quotes_split(str, strs, &i, &j);
		else
		{
			strs[i][j++] = **str;
			(*str)++;
		}
	}
	strs[i][j] = '\0';
	return (SUCCESS);
}

static int	handle_split_input(int words, char *str, char **strs, t_data *data)
{
	int	i;

	i = -1;
	while (++i < words)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !is_charset_split(*str))
		{
			if (!fill_words(i, &str, &(*strs), data))
				return (FAIL);
		}
		else if (*str && is_charset_split(*str))
		{
			if (!handle_delimiters(i, &str, &(*strs), data))
				return (FAIL);
		}
	}
	strs[i] = NULL;
	return (SUCCESS);
}

char	**split_input(char *str, t_data *data)
{
	int		words;
	char	**strs;

	data->input = &str;
	words = split_count_words(str, data);
	if (words == -1)
		return (NULL);
	strs = (char **)ft_calloc(1, sizeof(char *) * (words + 1));
	if (!strs)
		exit_error_str(str, "malloc()", data);
	if (!handle_split_input(words, str, strs, data))
		return (NULL);
	return (strs);
}
