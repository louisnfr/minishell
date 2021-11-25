/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:33 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/25 10:47:30 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*display_error_msg_simple_dot(char **str)
{
	ft_putstr_fd("bash: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	if (str)
		free_double_str(str);
	return (NULL);
}

int	display_error_msg_delimiter(int count, char delimiter)
{
	int	i;

	if (count == -1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (count)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		i = -1;
		while (++i < count)
			ft_putchar_fd(delimiter, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (FAIL);
}
