/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:26:59 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 13:11:52 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(char *str)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!is_charset_split(str[i]))
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
					i++;
				i++;
			}
			if (str[i] == '\"')
			{
				i++;
				while (str[i] && str[i] != '\"')
					i++;
				i++;
			}
			else
			{
				while (str[i] && !is_charset_split(str[i]))
					i++;
			}
			args++;
		}
		if (!check_delimiter(str, '|', &i, &args)
			|| !check_delimiter(str, '&', &i, &args)
			|| !check_delimiter(str, ';', &i, &args))
			return (-1);
		while (str[i] && ft_isspace(str[i]))
			i++;
	}
	return (args);
}

int	handle_words(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp[j] && !is_charset_split(tmp[j]))
		j++;
	free(tmp);
	tmp = NULL;
	strs[i] = (char *)malloc(sizeof(char) * (j + 1));
	if (!strs[i])
		return (0);
	j = 0;
	while (**str && !is_charset_split(**str))
	{
		if (**str == '\'')
		{
			(*str)++;
			while (**str && **str != '\'')
			{
				strs[i][j++] = **str;
				(*str)++;
			}
			(*str)++;
		}
		else if (**str == '\"')
		{
			(*str)++;
			while (**str && **str != '\"')
			{
				strs[i][j++] = **str;
				(*str)++;
			}
			(*str)++;
		}
		else
		{
			strs[i][j++] = **str;
			(*str)++;
		}
	}
	strs[i][j] = '\0';
	return (1);
}

char	**split_arguments(char *str)
{
	int		words;
	char	**strs;
	int		i;

	words = count_arguments(str);
	if (words == -1)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!is_charset_split(*str))
		{
			if (!handle_words(i, &str, &(*strs)))
				return (NULL);
		}
		else if (is_charset_split(*str))
		{
			if (!handle_delimiters(i, &str, &(*strs)))
				return (NULL);
		}
	}
	strs[i] = NULL;
	return (strs);
}
