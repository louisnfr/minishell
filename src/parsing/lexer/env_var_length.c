/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:37:17 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/06 15:42:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_variable(
	int *double_quotes, t_var *var, char *str, t_data *data)
{
	char	*env_key;

	env_key = NULL;
	env_key = get_env_key(str, &var->i);
	var->j += get_length_env_value(double_quotes, env_key, data);
	free(env_key);
	env_key = NULL;
	if (!str[var->i])
		var->j--;
}

static int	handle_special_cases(
	int *double_quotes, t_var *var, char *str)
{
	if (*double_quotes != -1 && str[var->i] && str[var->i] == '\'')
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

int	get_length_new_input(char *str, t_data *data)
{
	t_var	*var;
	int		double_quotes;
	int		length;

	var = init_var();
	if (!var || !str || !str[var->i])
		return (FAIL);
	double_quotes = 1;
	while (var->i < (int)ft_strlen(str) && str[var->i] && str[var->i + 1])
	{
		if (str[var->i] && str[var->i] == '\"')
			double_quotes *= -1;
		if (handle_special_cases(&double_quotes, var, str))
			continue ;
		if (str[var->i] && str[var->i + 1] && str[var->i] == '$'
			&& !is_charset_env(str[var->i + 1]))
			handle_env_variable(&double_quotes, var, str, data);
		else
			increment_i_j(var);
	}
	length = var->j++;
	free_var(var);
	return (length);
}
