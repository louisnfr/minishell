/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:00:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:41:54 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_fd_array(int **fd_array, int nb_of_pipes, t_data *data)
{
	int	i;

	i = -1;
	while (++i < nb_of_pipes)
	{
		safe_close_fd(fd_array[i][0], NULL, data);
		safe_close_fd(fd_array[i][1], NULL, data);
	}
	free_fd_array(nb_of_pipes, fd_array);
	exit_error_str(NULL, "malloc()", data);
}

void	exit_error_child(char **strs, char **strs2, char *error, t_data *data)
{
	if (strs)
		free_double_str(strs);
	if (strs2)
		free_double_str(strs2);
	if (data)
		clean_data(data);
	ft_putstr_fd("minishell: error ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\nexit\n", 2);
	exit(42);
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
