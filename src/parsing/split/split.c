/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:49:39 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 16:31:53 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_delimiters(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp && tmp[j] && is_charset_split(tmp[j]))
		j++;
	free(tmp);
	tmp = NULL;
	strs[i] = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!strs[i])
		return (0);
	j = 0;
	while (**str && is_delimiter_split(**str))
	{
		strs[i][j++] = **str;
		(*str)++;
	}
	strs[i][j] = '\0';
	return (1);
}

static int	get_count(char **str)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
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

t_bool	fill_words(int i, char **str, char **strs)
{
	int	j;

	strs[i] = (char *)ft_calloc(1, sizeof(char) * (get_count(str) + 1));
	if (!strs[i])
		return (FAIL);
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

int	handle_split_input(int words, char *str, char **strs)
{
	int	i;

	i = -1;
	while (++i < words)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !is_charset_split(*str))
		{
			if (!fill_words(i, &str, &(*strs)))
				return (FAIL);
		}
		else if (*str && is_charset_split(*str))
		{
			if (!handle_delimiters(i, &str, &(*strs)))
				return (FAIL);
		}
		if (strs[i] && str_is_equal(strs[i], "<<"))
			handle_heredoc_quotes(&i, &str, &(*strs));
	}
	strs[i] = NULL;
	return (SUCCESS);
}

char	**split_input(char *str)
{
	int		words;
	char	**strs;

	words = split_count_words(str);
	if (words == -1)
		return (NULL);
	strs = (char **)ft_calloc(1, sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	if (!handle_split_input(words, str, strs))
		return (NULL);
	return (strs);
}
