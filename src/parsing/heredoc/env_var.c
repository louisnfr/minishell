/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:08:45 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 13:19:03 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_double_dollars(t_var *var, char *str)
{
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

static int	heredoc_length_new_input(char *str, t_data *data)
{
	t_var	*var;
	int		length;

	var = init_var(data);
	if (!var || !str || !str[var->i])
		return (0);
	while (str && str[var->i] && str[var->i + 1])
	{
		if (heredoc_double_dollars(var, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& !is_charset_env(str[var->i + 1]))
			handle_env_variable(-1, var, str, data);
		else
			increment_i_j(var);
	}
	length = var->j++;
	free_var(var);
	return (length);
}

static int	heredoc_special_case(t_var *var, char *new_str, char *str)
{
	int	count;

	count = 0;
	if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
		&& str[var->i + 1] == '$')
	{
		while (str[var->i] && count++ < 2)
			new_str[var->j++] = str[var->i++];
		return (1);
	}
	return (0);
}

static int	heredoc_fill_new_input(char *new_str, char *str, t_data *data)
{
	t_var	*var;
	int		str_length;

	var = init_var(data);
	if (!var || !str || !str[var->i])
		return (FAIL);
	str_length = ft_strlen(str);
	while (var->i < str_length && str[var->i] && str[var->i + 1])
	{
		if (heredoc_special_case(var, new_str, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& !is_charset_env(str[var->i + 1]))
			fill_env_value(
				-1, new_str, var, get_env_val(str, &var->i, data));
		else
			new_str[var->j++] = str[var->i++];
	}
	if (var->i < str_length && str[var->i])
		new_str[var->j++] = str[var->i];
	new_str[var->j] = '\0';
	free_var(var);
	return (1);
}

char	*heredoc_env_variable(char *input, t_data *data)
{
	char	*new_input;
	int		new_length;

	new_input = NULL;
	new_length = heredoc_length_new_input(input, data);
	new_input = (char *)ft_calloc(1, sizeof(char) * (new_length + 1));
	if (!new_input)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	heredoc_fill_new_input(new_input, input, data);
	clean_free(&input);
	return (new_input);
}
