/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:37:17 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:24:43 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_variable(
	int double_quotes, t_var *var, char *str, t_data *data)
{
	char	*env_key;

	env_key = NULL;
	env_key = get_env_key(str, &var->i, var, data);
	var->j += get_length_env_value(double_quotes, env_key, data);
	clean_free(&env_key);
	env_key = NULL;
	if (!str[var->i])
		var->j--;
}

static int	handle_special_cases(
	int double_quotes, t_var *var, char *str)
{
	if (double_quotes != -1 && str[var->i] && str[var->i] == '\'')
	{
		var->i++;
		var->j++;
		while (str[var->i] && str[var->i] != '\'')
		{
			var->i++;
			var->j++;
		}
		if (!str[var->i + 1])
			var->j--;
	}
	if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
		&& str[var->i + 1] == '$')
	{
		var->i += 2;
		if (str[var->i])
			var->j += 2;
		else
			var->j++;
		return (1);
	}
	return (0);
}

void	increment_i_j(t_var *var)
{
	var->i++;
	var->j++;
}

static void	dollar_case(t_var *var, char *str, t_data *data)
{
	char	quote;

	if (!str[var->i + 1])
		return ;
	if (ft_isdigit(str[var->i + 1]))
		var->i += 2;
	else if ((str[var->i + 1] == '\"' || str[var->i + 1] == '\'')
		&& str[var->i + 2])
	{
		quote = str[var->i + 1];
		var->i += 2;
		while (str[var->i] && str[var->i] != quote)
			increment_i_j(var);
		var->i++;
	}
	else if (str[var->i + 1] == '=')
	{
		var->i += 2;
		var->j += 2;
	}
	else if (!is_charset_env(str[var->i + 1]))
		handle_env_variable(data->double_quotes, var, str, data);
	else
		increment_i_j(var);
}

int	get_length_new_input(
	char *ret_value, char *pid_value, char *str, t_data *data)
{
	t_var	*var;
	int		length;

	var = secured_init_var_env(pid_value, ret_value, str, data);
	if (!str || !str[var->i])
		return (error_new_input(var, str));
	data->double_quotes = 1;
	while (var->i < (int)ft_strlen(str) && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
			data->double_quotes *= -1;
		if (handle_special_cases(data->double_quotes, var, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$')
			dollar_case(var, str, data);
		else
			increment_i_j(var);
	}
	length = ++var->j;
	free_var(var);
	return (length);
}
