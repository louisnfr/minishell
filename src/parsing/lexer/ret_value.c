/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:47:11 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 15:02:07 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_length_quotes(int *length, int *count, int *i, char *str)
{
	if (str[*i] && str[*i] == '\"')
	{
		increment_var(i, length);
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
		increment_var(i, length);
	}
	if (str[*i] && str[*i] == '\'')
	{
		increment_var(i, length);
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		increment_var(i, length);
	}
}

static int	get_length(char *str, int value_length)
{
	int	i;
	int	length;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	length = ft_strlen(str);
	while (i < (int)ft_strlen(str) && str[i] && str[i + 1])
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

static void	fill_quotes(t_var *var, char *str, char *new_str, char *value)
{
	if (str[var->i] && str[var->i] == '\"')
	{
		var->i++;
		while (str[var->i] && str[var->i] != '\"')
		{
			if (str[var->i] && str[var->i + 1]
				&& str[var->i] == '$' && str[var->i + 1] == '?')
				fill_with_value(var, new_str, value);
			else
				new_str[var->j++] = str[var->i++];
		}
		var->i++;
	}
	if (str[var->i] && str[var->i] == '\'')
	{
		var->i++;
		while (str[var->i] && str[var->i] != '\'')
			new_str[var->j++] = str[var->i++];
		var->i++;
	}
}

static t_bool	fill_new_str(char *str, char *new_str, char *value)
{
	int		str_length;
	t_var	*var;

	var = init_var();
	if (!var)
		return (FAIL);
	str_length = ft_strlen(str);
	while (str && var->i < str_length && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && (str[var->i] == '\'' || str[var->i] == '\"'))
			fill_quotes(var, str, new_str, value);
		else if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& str[var->i + 1] == '?')
			fill_with_value(var, new_str, value);
		else
			new_str[var->j++] = str[var->i++];
	}
	if (str && var->i < str_length && str[var->i])
		new_str[var->j++] = str[var->i];
	new_str[var->j] = '\0';
	free_var(var);
	return (SUCCESS);
}

char	*transform_ret_value(
	char *str, char *value, char *pid_value, t_data *data)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = get_length(str, ft_strlen(value));
	new_str = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_str || !fill_new_str(&(*str), &(*new_str), value))
	{
		clean_free(&value);
		clean_free(&pid_value);
		clean_free(&new_str);
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(str, "malloc()", data);
	}
	clean_free(&str);
	return (new_str);
}
