/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:46:54 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 15:02:25 by efrancon         ###   ########.fr       */
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

	if (!str)
		return (0);
	length = setup_variables(&i, &count, &double_quotes, str);
	while (i < (int)ft_strlen(str) && str[i] && str[i + 1])
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

static void	fill_simple_quotes(t_var *var, char *str, char *new_str)
{
	new_str[var->j++] = str[var->i++];
	while (str[var->i] && str[var->i] != '\'')
		new_str[var->j++] = str[var->i++];
}

static t_bool	fill_new_str(
	char *str, char *new_str, char *value, char character)
{
	int		double_quotes;
	t_var	*var;

	var = init_var();
	if (!var)
		return (FAIL);
	double_quotes = 1;
	while (str && var->i < (int)ft_strlen(str)
		&& str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
			double_quotes *= -1;
		if (double_quotes != -1 && str[var->i] && str[var->i] == '\'')
			fill_simple_quotes(var, str, new_str);
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& str[var->i + 1] == character)
			fill_with_value(var, new_str, value);
		else
			new_str[var->j++] = str[var->i++];
	}
	if (str && str[var->i] && var->i < (int)ft_strlen(str))
		new_str[var->j++] = str[var->i];
	new_str[var->j] = '\0';
	free_var(var);
	return (SUCCESS);
}

char	*transform_pid_value(
	char *str, char *value, char *ret_value, t_data *data)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = get_length(str, ft_strlen(value), '$');
	new_str = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_str || !fill_new_str(&(*str), &(*new_str), value, '$'))
	{
		clean_free(&ret_value);
		clean_free(&value);
		clean_free(&new_str);
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		exit_error_str(str, "malloc()", data);
	}
	clean_free(&str);
	return (new_str);
}
