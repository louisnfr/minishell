/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:45:46 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 18:37:44 by efrancon         ###   ########.fr       */
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

char	*heredoc_special_value(
	char *str, char *value, char character, t_data *data)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = heredoc_get_length(str, ft_strlen(value), character);
	new_str = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_str)
	{
		clean_free(&str);
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(value, "malloc()", data);
	}
	heredoc_fill_new_str(&(*str), &(*new_str), value, character);
	clean_free(&str);
	return (new_str);
}
