/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:17:18 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_cases(
	int double_quotes, t_var *var, char *new_str, char *str)
{
	int	count;

	count = 0;
	if (double_quotes != -1 && str[var->i] && str[var->i] == '\'')
	{
		new_str[var->j++] = str[var->i++];
		while (str[var->i] && str[var->i] != '\'')
			new_str[var->j++] = str[var->i++];
	}
	if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
		&& str[var->i + 1] == '$')
	{
		while (str[var->i] && count++ < 2)
			new_str[var->j++] = str[var->i++];
		return (1);
	}
	return (0);
}

static void	fill_dollar_case(t_var *var, char *new_str, char *str, t_data *data)
{
	char	quote;

	if (ft_isdigit(str[var->i + 1]))
		var->i += 2;
	else if ((str[var->i + 1] == '\"' || str[var->i + 1] == '\'')
		&& str[var->i + 2])
	{
		quote = str[var->i + 1];
		var->i += 2;
		while (str[var->i] && str[var->i] != quote)
			new_str[var->j++] = str[var->i++];
		var->i++;
	}
	else if (str[var->i + 1] == '=')
	{
		new_str[var->j++] = str[var->i++];
		new_str[var->j++] = str[var->i++];
	}
	else if (!is_charset_env(str[var->i + 1]))
		fill_env_value(new_str, var, str, data);
	else
		new_str[var->j++] = str[var->i++];
}

static int	fill_new_input(char *new_str, char *str, t_data *data)
{
	t_var	*var;

	var = init_var();
	if (!var || !str || !str[var->i])
		return (error_new_input(var, str));
	data->double_quotes = 1;
	while (var->i < (int)ft_strlen(str) && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
			data->double_quotes *= -1;
		if (handle_special_cases(data->double_quotes, var, new_str, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$')
			fill_dollar_case(var, new_str, str, data);
		else
			new_str[var->j++] = str[var->i++];
	}
	if (var->i < (int)ft_strlen(str) && str[var->i])
		new_str[var->j++] = str[var->i];
	new_str[var->j] = '\0';
	free_var(var);
	return (SUCCESS);
}

static char	*handle_special_case(char *input, t_data *data)
{
	if (str_is_equal(input, "$\"\""))
	{
		clean_free(&input);
		return (safe_strdup("\"\"", data));
	}
	clean_free(&input);
	return (safe_strdup("\'\'", data));
}

char	*parse_env_variable(
	char *ret_value, char *pid_value, char *input, t_data *data)
{
	char	*new_input;
	int		new_length;

	new_input = NULL;
	if (str_is_equal(input, "$\"\"") || str_is_equal(input, "$\'\'"))
		return (handle_special_case(input, data));
	new_length = get_length_new_input(ret_value, pid_value, input, data);
	new_input = (char *)ft_calloc(1, sizeof(char) * (new_length + 1));
	if (!new_input || (fill_new_input(new_input, input, data) == -1))
	{
		if (data->argv && *data->argv)
			free_double_str(*data->argv);
		clean_free(&pid_value);
		clean_free(&ret_value);
		clean_free(&new_input);
		exit_error_str(input, "malloc()", data);
	}
	clean_free(&input);
	if (new_input && new_input[0] == '\0')
		clean_free(&new_input);
	return (new_input);
}
