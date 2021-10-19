/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_special_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:08:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 12:14:39 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_get_length(char *str, int value_length, char character)
{
	int	i;
	int	length;
	int	count;
	int	str_length;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	str_length = ft_strlen(str);
	length = ft_strlen(str);
	while (i < str_length && str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] == character)
		{
			count++;
			i++;
		}
		i++;
	}
	if (count)
		length = length + count * (value_length - 2);
	return (length);
}

static void	heredoc_fill_new_str(
	char *str, char *new_str, char *value, char character)
{
	int	i;
	int	j;
	int	k;
	int	str_length;

	i = 0;
	j = 0;
	if (!str || !str[i])
		return ;
	str_length = ft_strlen(str);
	while (i < str_length && str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] == character)
		{
			k = 0;
			while (value && value[k])
				new_str[j++] = value[k++];
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	if (i < str_length && str[i])
		new_str[j++] = str[i];
	new_str[j] = '\0';
}

char	*heredoc_special_value(char *str, char *value, char character)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = heredoc_get_length(str, ft_strlen(value), character);
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_str)
		return (NULL);
	heredoc_fill_new_str(&(*str), &(*new_str), value, character);
	clean_free(&str);
	return (new_str);
}
