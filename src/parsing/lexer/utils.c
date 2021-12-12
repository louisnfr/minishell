/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:41:45 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 17:59:51 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_with_value(t_var *var, char *new_str, char *value)
{
	int	k;

	k = 0;
	while (value && value[k])
		new_str[var->j++] = value[k++];
	var->i += 2;
}

void	increment_var(int *i, int *length)
{
	(*i)++;
	(*length)--;
}

int	setup_variables(int *i, int *count, int *double_quotes, char *str)
{
	*i = 0;
	*count = 0;
	*double_quotes = 1;
	return (ft_strlen(str));
}

void	free_var(t_var *var)
{
	free(var);
	var = NULL;
}

t_var	*init_var(t_data *data)
{
	t_var	*var;

	var = (t_var *)ft_calloc(1, sizeof(t_var));
	if (data && !var)
		exit_error_str(NULL, "malloc()", data); // leaks non verifie
	else if (!data && !var)
		return (NULL);
	var->i = 0;
	var->j = 0;
	return (var);
}
