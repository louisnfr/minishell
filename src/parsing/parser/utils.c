/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/05 14:25:31 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_delimiter(char *str)
{
	if (str_is_equal(str, "|"))
		return (PIPE);
	if (str_is_equal(str, "&&"))
		return (AND);
	if (str_is_equal(str, "||"))
		return (OR);
	if (str_is_equal(str, ";"))
		return (SEMICOLON);
	return (0);
}

t_bool	is_delimiter(char *str)
{
	return (str_is_equal(str, "&&")
		|| str_is_equal(str, ";")
		|| str_is_equal(str, "|")
		|| str_is_equal(str, "||"));
}

int	get_redirection(char *str)
{
	if (str_is_equal(str, "<"))
		return (LEFT_MARK);
	if (str_is_equal(str, "<<"))
		return (HEREDOC);
	if (str_is_equal(str, ">"))
		return (RIGHT_MARK);
	if (str_is_equal(str, ">>"))
		return (DOUBLE_RIGHT_MARK);
	if (str_is_equal(str, "2>"))
		return (ERROR);
	if (str_is_equal(str, "2>>"))
		return (DOUBLE_ERROR);
	if (str_is_equal(str, "2>&1"))
		return (ERROR_AND_STDOUT);
	return (0);
}

t_bool	is_redirection(char *str)
{
	return (str_is_equal(str, "<")
		|| str_is_equal(str, "<<")
		|| str_is_equal(str, ">")
		|| str_is_equal(str, ">>")
		|| str_is_equal(str, "2>")
		|| str_is_equal(str, "2>>")
		|| str_is_equal(str, "2>&1"));
}

void	free_fd_array(int size, int **fd_array)
{
	int	i;

	i = 0;
	while (i < size)
		free(fd_array[i++]);
	free(fd_array);
}
