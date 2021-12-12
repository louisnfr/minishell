/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:49:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 21:42:12 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_normal_words(char *str, t_data *data)
{
	char	quote;
	int		str_length;

	str_length = ft_strlen(str);
	while (data->i < str_length && str[data->i]
		&& !is_charset_split(str[data->i]))
	{
		if (str[data->i] && (str[data->i] == '\'' || str[data->i] == '\"'))
		{
			quote = str[data->i++];
			while (str[data->i] && str[data->i] != quote)
				data->i++;
			data->i++;
		}
		else
			data->i++;
	}
}

static t_bool	check_all_delimiters(char *str, int *words, t_data *data)
{
	if (!check_delimiter(str, '|', words, data)
		|| !check_delimiter(str, ';', words, data)
		|| !check_delimiter(str, '&', words, data)
		|| !check_delimiter(str, '>', words, data)
		|| !check_delimiter(str, '<', words, data)
		|| !check_delimiter(str, '(', words, data)
		|| !check_delimiter(str, ')', words, data))
		return (FAIL);
	return (SUCCESS);
}

int	split_count_words(char *str, t_data *data)
{
	int	words;
	int	str_length;

	data->i = 0;
	words = 0;
	str_length = ft_strlen(str);
	while (str && data->i < str_length && str[data->i])
	{
		while (str[data->i] && ft_isspace(str[data->i]))
			data->i++;
		if (str[data->i] && !is_charset_split(str[data->i]))
		{
			count_normal_words(str, data);
			words++;
		}
		if (!check_all_delimiters(str, &words, data))
			return (-1);
	}
	data->i = 0;
	return (words);
}

void	exit_error_split(char **strs, t_data *data)
{
	if (data->input && *data->input)
		clean_free(data->input);
	exit_error_strs(strs, "malloc()", data);
}
