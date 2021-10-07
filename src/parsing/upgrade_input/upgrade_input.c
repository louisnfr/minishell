/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:34 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 19:49:12 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*upgrade_input(char *input, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!ft_strchr(input, '$'))
		return (input);
	input = parse_env_variable(input, data);
	ret_value = ft_itoa(data->ret_value);
	pid_value = ft_itoa(data->pid);
	input = transform_special_value(input, pid_value, '$');
	input = transform_special_value(input, ret_value, '?');
	clean_free(&pid_value);
	clean_free(&ret_value);
	return (input);
}
