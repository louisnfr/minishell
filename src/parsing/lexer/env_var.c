/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/20 13:57:24 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_cases(
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

t_bool	is_ending(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (TRUE);
	return (FALSE);
}

t_bool	put_space(char *str, int k, t_var *var, t_data *data)
{
	if (!k)
	{
		if (str[0] && str[0] == '$')
			return (FALSE);
		return (TRUE);
	}
	if (is_ending(data->env_value, k))
	{
		if (str[var->i])
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

void	fill_env_value(
	char *new_str, t_var *var, char *str, t_data *data)
{
	int	k;

	(void)str;
	if (!data->env_value)
		return ;
	k = 0;
	if (data->double_quotes == -1)
	{
		while (data->env_value && data->env_value[k])
			new_str[var->j++] = data->env_value[k++];
	}
	else
	{
		while (data->env_value && k < (int)ft_strlen(data->env_value) && data->env_value[k])
		{
			if (data->env_value[k] && ft_isspace(data->env_value[k]))
			{
				if (put_space(str, k, var, data))
					new_str[var->j++] = data->env_value[k++];
				while (data->env_value[k] && ft_isspace(data->env_value[k]))
					k++;
			}
			else
				new_str[var->j++] = data->env_value[k++];
		}
	}
}

static void	fill_dollar_case(t_var *var, char *new_str, char *str, t_data *data)
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
			new_str[var->j++] = str[var->i++];
		var->i++;
	}
	else if (str[var->i + 1] == '=')
	{
		new_str[var->j++] = str[var->i++];
		new_str[var->j++] = str[var->i++];
	}
	else if (!is_charset_env(str[var->i + 1]))
	{
		data->env_value = get_env_val(str, &var->i, data);
		fill_env_value(new_str, var, str, data);
		data->env_value = NULL;
	}
	else
		new_str[var->j++] = str[var->i++];
}

static int	fill_new_input(char *new_str, char *str, t_data *data)
{
	t_var	*var;

	var = init_var(data);
	if (!var || !str || !str[var->i])
		return (FAIL);
	data->double_quotes = 1;
	data->count_quotes = 0;
	while (var->i < (int)ft_strlen(str) && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
		{
			data->double_quotes *= -1;
			data->count_quotes++;
		}
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

char	*parse_env_variable(char *input, t_data *data)
{
	char	*new_input;
	int		new_length;

	new_input = NULL;
	new_length = get_length_new_input(input, data);
	new_input = (char *)ft_calloc(1, sizeof(char) * (new_length + 1));
	if (!new_input)
	{
		clean_free(&input);
		return ((char *)exit_error_void(NULL, "malloc()", data));
	}
	fill_new_input(new_input, input, data);
	clean_free(&input);
	if (new_input && new_input[0] == '\0')
		clean_free(&new_input);
	return (new_input);
}
