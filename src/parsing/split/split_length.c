/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:17:06 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/02 10:19:43 by EugenieFran      ###   ########.fr       */
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

int	split_count_words(char *str, t_data *data)
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
		if (!check_delimiter(str, '|', &i, &words, data)
			|| !check_delimiter(str, '&', &i, &words, data)
			|| !check_delimiter(str, ';', &i, &words, data)
			|| !check_delimiter(str, '>', &i, &words, data)
			|| !check_delimiter(str, '<', &i, &words, data)
			|| !check_delimiter(str, '(', &i, &words, data)
			|| !check_delimiter(str, ')', &i, &words, data))
			return (-1);
	}
	return (words);
}
