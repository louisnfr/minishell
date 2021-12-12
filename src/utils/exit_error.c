/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:00:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 14:25:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*exit_error_void(void *return_value, char *error, t_data *data)
{
	if (data)
		clean_data(data);
	ft_putstr_fd("minishell: error ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\nexit\n", 2);
	exit(1);
	return (return_value);
}

t_bool	exit_error_bool(char *error, t_data *data)
{
	if (data)
		clean_data(data);
	ft_putstr_fd("minishell: error ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\nexit\n", 2);
	exit(1);
	return (FAIL);
}

void	exit_error_str(char *str, char *error, t_data *data)
{
	if (str)
		clean_free(&str);
	if (data)
		clean_data(data);
	ft_putstr_fd("minishell: error ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\nexit\n", 2);
	exit(1);
}

void	exit_error_strs(char **strs, char *error, t_data *data)
{
	if (strs)
		free_double_str(strs);
	if (data)
		clean_data(data);
	ft_putstr_fd("minishell: error ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\nexit\n", 2);
	exit(1);
}
