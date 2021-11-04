/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:49:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 16:31:36 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_normal_words(char *str, int *i)
{
	char	quote;
	int		str_length;

	str_length = ft_strlen(str);
	while (*i < str_length && str[*i] && !is_charset_split(str[*i]))
	{
		if (str[*i] && (str[*i] == '\'' || str[*i] == '\"'))
		{
			quote = (*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}

t_bool	check_all_delimiters(char *str, int *i, int *words)
{
	if (!check_delimiter(str, '|', i, words)
		|| !check_delimiter(str, ';', i, words)
		|| !check_delimiter(str, '&', i, words)
		|| !check_delimiter(str, '>', i, words)
		|| !check_delimiter(str, '<', i, words)
		|| !check_delimiter(str, '(', i, words)
		|| !check_delimiter(str, ')', i, words))
		return (FAIL);
	return (SUCCESS);
}

int	split_count_words(char *str)
{
	int	words;
	int	i;
	int	str_length;

	i = 0;
	words = 0;
	str_length = ft_strlen(str);
	while (str && i < str_length && str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !is_charset_split(str[i]))
		{
			count_normal_words(str, &i);
			words++;
		}
		if (!check_all_delimiters(str, &i, &words))
			return (-1);
	}
	return (words);
}
