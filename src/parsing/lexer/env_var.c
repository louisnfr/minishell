/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/06 15:13:31 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_cases(
	t_var *var, int *double_quotes, char *new_str, char *str)
{
	int	count;

	count = 0;
	if (*double_quotes != -1 && str[var->i] && str[var->i] == '\'')
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

void	fill_env_value(
	int *double_quotes, char *new_str, t_var *var, char *value)
{
	int	k;

	if (!value)
		return ;
	k = 0;
	if (*double_quotes == -1)
	{
		while (value && value[k])
			new_str[var->j++] = value[k++];
	}
	else
	{
		while (value && k < (int)ft_strlen(value) && value[k])
		{
			if (value[k] && ft_isspace(value[k]))
			{
				new_str[var->j++] = value[k++];
				while (value[k] && ft_isspace(value[k]))
					k++;
			}
			else
				new_str[var->j++] = value[k++];
		}
	}
}

static int	fill_new_input(char *new_str, char *str, t_data *data)
{
	t_var	*var;
	int		double_quotes;

	var = init_var();
	if (!var || !str || !str[var->i])
		return (FAIL);
	double_quotes = 1;
	while (var->i < (int)ft_strlen(str) && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
			double_quotes *= -1;
		if (handle_special_cases(var, &double_quotes, new_str, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& !is_charset_env(str[var->i + 1]))
			fill_env_value(
				&double_quotes, new_str, var, get_env_val(str, &var->i, data));
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
		return (NULL);
	fill_new_input(new_input, input, data);
	clean_free(&input);
	return (new_input);
}
