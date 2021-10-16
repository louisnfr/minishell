/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:26:59 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/16 14:32:15 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_quotes(char **str, char **strs, int *i, int *j)
{
	if (**str && **str == '\'')
	{
		(*str)++;
		while (**str && **str != '\'')
		{
			strs[*i][(*j)++] = **str;
			(*str)++;
		}
		(*str)++;
	}
	else if (**str && **str == '\"')
	{
		(*str)++;
		while (**str && **str != '\"')
		{
			strs[*i][(*j)++] = **str;
			(*str)++;
		}
		(*str)++;
	}
}

void	count_in_quotes(int *j, char *tmp)
{
	char	quote;

	quote = tmp[*j];
	(*j)++;
	while (tmp[*j] && tmp[*j] != quote)
		(*j)++;
	(*j)++;
}

t_bool	fill_words(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp[j] && !is_charset_split(tmp[j]))
	{
		if (tmp[j] && (tmp[j] == '\'' || tmp[j] == '\"'))
			count_in_quotes(&j, tmp);
		else
			j++;
	}
	clean_free(&tmp);
	strs[i] = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!strs[i])
		return (FAIL);
	j = 0;
	while (**str && !is_charset_split(**str))
	{
		if (**str && (**str == '\'' || **str == '\"'))
			fill_quotes(str, strs, &i, &j);
		else
		{
			strs[i][j++] = **str;
			(*str)++;
		}
	}
	strs[i][j] = '\0';
	return (SUCCESS);
}

t_bool	handle_heredoc_quotes(int *i, char **str, char **strs)
{
	int		j;
	char	*tmp;
	char	charset;

	while (**str && ft_isspace(**str))
		(*str)++;
	if (!(**str) || (**str && **str != '\'' && **str != '\"'))
		return (SUCCESS);
	charset = **str;
	j = 1;
	tmp = ft_strdup(*str);
	while (tmp[j] && tmp[j] != charset)
		j++;
	free(tmp);
	tmp = NULL;
	strs[++(*i)] = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!strs[*i])
		return (FAIL);
	j = 0;
	strs[*i][j++] = **str;
	(*str)++;
	while (**str)
	{
		strs[*i][j++] = **str;
		(*str)++;
		if (**str && **str == charset)
		{
			strs[*i][j++] = **str;
			break ;
		}
	}
	strs[*i][j] = '\0';
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

char	**split_input(char *str, t_data *data)
{
	int		words;
	char	**strs;

	words = split_count_words(str, data);
	if (words == -1)
		return (NULL);
	strs = (char **)ft_calloc(1, sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	if (!handle_split_input(words, str, strs))
		return (NULL);
	return (strs);
}
