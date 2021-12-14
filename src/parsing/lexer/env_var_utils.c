/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:09 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 10:35:40 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset_env(char c)
{
	return ((c >= 32 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 126));
}

static int	count_length(char *env_value, int value_length)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (i < value_length && env_value[i])
	{
		if (env_value[i] && ft_isspace(env_value[i]))
		{
			i++;
			length++;
			while (env_value[i] && ft_isspace(env_value[i]))
				i++;
		}
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

int	get_length_env_value(int double_quotes, char *env_key, t_data *data)
{
	char	*env_value;
	int		value_length;
	int		length;

	env_value = NULL;
	env_value = get_env(env_key, data->env);
	if (!env_value)
		return (0);
	value_length = ft_strlen(env_value);
	if (double_quotes == -1)
		return (value_length);
	length = count_length(env_value, value_length);
	return (length);
}

char	*get_env_key(char *str, int *i, t_var *var, t_data *data)
{
	char	*env_var;
	int		var_length;
	int		j;

	j = *i + 1;
	var_length = 0;
	env_var = NULL;
	while (str && str[j] && !is_charset_env(str[j++]))
		var_length++;
	if (var_length)
	{
		env_var = NULL;
		env_var = (char *)ft_calloc(1, sizeof(char) * (var_length + 1));
		if (!env_var)
			exit_error_env_key(str, var, data);
		var_length = 0;
		while (str && str[++(*i)] && !is_charset_env(str[*i]))
			env_var[var_length++] = str[*i];
		env_var[var_length] = '\0';
	}
	return (env_var);
}

char	*get_env_val(char *str, int *i, t_var *var, t_data *data)
{
	char	*env_key;
	char	*env_value;

	env_key = NULL;
	env_value = NULL;
	env_key = get_env_key(str, &(*i), var, data);
	env_value = get_env(env_key, data->env);
	clean_free(&env_key);
	return (env_value);
}
