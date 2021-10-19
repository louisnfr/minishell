/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:16:28 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 11:18:29 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_length_quotes(int *length, int *count, int *i, char *str)
{
	if (str[*i] && str[*i] == '\"')
	{
		(*i)++;
		(*length)--;
		while (str[*i] && str[*i] != '\"')
		{
			if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '?')
			{
				(*count)++;
				*i += 2;
			}
			else
				(*i)++;
		}
		(*i)++;
		(*length)--;
	}
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		(*length)--;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		(*i)++;
		(*length)--;
	}
}

static int	get_length(char *str, int value_length)
{
	int	i;
	int	length;
	int	count;
	int	str_length;

	i = 0;
	count = 0;
	str_length = ft_strlen(str);
	if (!str)
		return (0);
	length = ft_strlen(str);
	while (i < str_length && str[i] && str[i + 1])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			get_length_quotes(&length, &count, &i, str);
		else if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '?')
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	if (count)
		length = length + count * (value_length - 2);
	return (length);
}

static void	fill_quotes(int *i, int *j, char *str, char *new_str, char *value)
{
	int	k;

	if (str[*i] && str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
		{
			if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '?')
			{
				k = 0;
				while (value && value[k])
					new_str[(*j)++] = value[k++];
				*i += 2;
			}
			else
				new_str[(*j)++] = str[(*i)++];
		}
		(*i)++;
	}
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			new_str[(*j)++] = str[(*i)++];
		(*i)++;
	}
}

void	fill_new_str(char *str, char *new_str, char *value)
{
	int	i;
	int	j;
	int	k;
	int	str_length;

	i = 0;
	j = 0;
	str_length = ft_strlen(str);
	if (!str)
		return ;
	while (i < str_length && str[i] && str[i + 1])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			fill_quotes(&i, &j, str, new_str, value);	
		else if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '?')
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

char	*transform_ret_value(char *str, char *value)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = get_length(str, ft_strlen(value));
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_str)
		return (NULL);
	fill_new_str(&(*str), &(*new_str), value);
	clean_free(&str);
	return (new_str);
}
