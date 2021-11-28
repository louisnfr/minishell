/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:50:10 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/28 12:43:45 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset_split(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == ';' || c == '<'
		|| c == '>' || c == '(' || c == ')');
}

int	is_delimiter_split(char c)
{
	return (c == '&' || c == '|' || c == ';' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}

void	fill_quotes_split(char **str, char **strs, int *i, int *j)
{
	if (**str && **str == '\'')
	{
		strs[*i][(*j)++] = **str;
		(*str)++;
		while (**str && **str != '\'')
		{
			strs[*i][(*j)++] = **str;
			(*str)++;
		}
		strs[*i][(*j)++] = **str;
		(*str)++;
	}
	else if (**str && **str == '\"')
	{
		strs[*i][(*j)++] = **str;
		(*str)++;
		while (**str && **str != '\"')
		{
			strs[*i][(*j)++] = **str;
			(*str)++;
		}
		strs[*i][(*j)++] = **str;
		(*str)++;
	}
}

void	count_in_quotes_split(int *j, char *tmp)
{
	char	quote;

	quote = tmp[*j];
	(*j)++;
	while (tmp[*j] && tmp[*j] != quote)
		(*j)++;
	(*j)++;
}

t_bool	malloc_strs(int i, char **str, char **strs, t_data *data)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = safe_strdup(*str, data);
	while (tmp && tmp[j] && is_charset_split(tmp[j]))
		j++;
	clean_free(&tmp);
	strs[i] = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!strs[i])
		return (FAIL);
	return (SUCCESS);
}
