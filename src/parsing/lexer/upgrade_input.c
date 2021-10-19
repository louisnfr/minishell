/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:34 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 10:26:53 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*upgrade_input(char *input, t_data *data)
{
	char	*pid_value;

	if (!ft_strchr(input, '$'))
		return (input);
	input = parse_env_variable(input, data);
	pid_value = ft_itoa(data->pid);
	input = transform_pid_value(input, pid_value);
	clean_free(&pid_value);
	return (input);
}
