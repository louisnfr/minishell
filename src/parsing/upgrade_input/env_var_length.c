/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:37:17 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/14 22:58:17 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_variable(int *i, int *length, char *str, t_data *data)
{
	char	*env_key;

	env_key = NULL;
	env_key = get_env_key(str, &(*i));
	(*length) += get_length_env_value(env_key, data);
	free(env_key);
	env_key = NULL;
	if (!str[*i])
		(*length)--;
}

int	handle_simple_quotes_and_double_dollars(int *i, int *length, char *str)
{
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		(*length)++;
		while (str[*i] && str[*i] != '\'')
		{
			(*i)++;
			(*length)++;
		}	
		if (!str[*i + 1])
			(*length)--;
	}
	if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '$')
	{
		(*i) += 2;
		if (str[*i])
			(*length) += 2;
		else
			(*length)++;
		return (1);
	}
	return (0);
}

int	get_length_new_input(char *str, t_data *data)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	if (!str || !str[i])
		return (0);
	while (str && str[i] && str[i + 1])
	{
		if (handle_simple_quotes_and_double_dollars(&i, &length, str))
			continue ;
		if (str[i] && str[i + 1] && str[i] == '$'
			&& !is_charset_env(str[i + 1]))
			handle_env_variable(&i, &length, str, data);
		else
		{
			i++;
			length++;
		}
	}
	return (++length);
}
