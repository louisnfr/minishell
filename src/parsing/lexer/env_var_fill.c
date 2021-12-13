/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:30:46 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 18:54:17 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_ending(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (TRUE);
	return (FALSE);
}

static t_bool	put_space(char *str, int k, t_var *var, t_data *data)
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

static t_bool	get_env_value(t_var *var, char *str, t_data *data)
{
	data->env_value = NULL;
	data->env_value = get_env_val(str, &var->i, var, data);
	if (!data->env_value)
		return (FAIL);
	return (SUCCESS);
}

void	fill_env_value(
	char *new_str, t_var *var, char *str, t_data *data)
{
	int	k;

	if (!get_env_value(var, str, data))
		return ;
	k = 0;
	if (data->double_quotes == -1)
	{
		while (data->env_value && data->env_value[k])
			new_str[var->j++] = data->env_value[k++];
	}
	else
	{
		while (k < (int)ft_strlen(data->env_value) && data->env_value[k])
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
