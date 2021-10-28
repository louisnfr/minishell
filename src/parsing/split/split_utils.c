/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:25 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 11:58:52 by EugenieFran      ###   ########.fr       */
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
	return (c == '&' || c == '|' || c == ';'|| c == '<' || c == '>'
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
