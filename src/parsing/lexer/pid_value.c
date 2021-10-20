/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:16:28 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/20 13:24:56 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_length_simple_quotes(int *double_quotes, int *i, char *str)
{
	if (*double_quotes != -1 && str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
}

static int	get_length(char *str, int value_length, char character)
{
	int	i;
	int	length;
	int	count;
	int	double_quotes;
	int	str_length;

	i = 0;
	count = 0;
	double_quotes = 1;
	str_length = ft_strlen(str);
	if (!str)
		return (0);
	length = ft_strlen(str);
	while (str[i] && str[i + 1] && i < str_length)
	{
		if (str[i] && str[i] == '\"')
			double_quotes *= -1;
		get_length_simple_quotes(&double_quotes, &i, str);
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == character)
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

static void	fill_simple_quotes(int *double_quotes, char *new_str, char *str, int *i, int *j)
{
	if (*double_quotes != -1 && str[*i] && str[*i] == '\'')
	{
		new_str[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != '\'')
			new_str[(*j)++] = str[(*i)++];
	}
}

static void	fill_new_str(char *str, char *new_str, char *value, char character)
{
	int	i;
	int	j;
	int	k;
	int	double_quotes;
	int	str_length;

	i = 0;
	j = 0;
	double_quotes = 1;
	str_length = ft_strlen(str);
	if (!str)
		return ;
	while (str[i] && str[i + 1] && i < str_length)
	{
		if (str[i] && str[i] == '\"')
			double_quotes *= -1;
		fill_simple_quotes(&double_quotes, new_str, str, &i, &j);
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == character)
		{
			k = 0;
			while (value && value[k])
				new_str[j++] = value[k++];
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	if (str[i] && i < str_length)
		new_str[j++] = str[i];
	new_str[j] = '\0';
}

char	*transform_pid_value(char *str, char *value)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = get_length(str, ft_strlen(value), '$');
	new_str = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_str)
		return (NULL);
	fill_new_str(&(*str), &(*new_str), value, '$');
	clean_free(&str);
	return (new_str);
}
