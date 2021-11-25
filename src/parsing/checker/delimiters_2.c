/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:23 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/25 11:10:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_left_marks(char *str, int j)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[j + i] && str[j + i] == '<')
	{
		i++;
		count++;
	}
	if (count > 0 && count < 3)
		return (0);
	if (count == 3)
		return (-1);
	if (count == 4)
		return (1);
	if (count == 5)
		return (2);
	if (count > 5)
		return (3);
	return (0);
}

int	check_right_marks(char *str, int j)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[j + i] && str[j + i] == '>')
	{
		i++;
		count++;
	}
	if (count > 0 && count < 3)
		return (0);
	if (count == 3)
		return (1);
	if (count > 3)
		return (2);
	return (0);
}

int	is_error_redir(char *str, int j)
{
	if (j < 2)
		return (FAIL);
	if ((str[j - 2] && str[j - 2] == '2') && (str[j - 1] && str[j - 1] == '>')
		&& (str[j + 1] && str[j + 1] == '1'))
		return (TRUE);
	return (FAIL);
}

t_bool	check_error_redir(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j == *i)
		return (TRUE);
	return (FALSE);
}

t_bool	check_beginning(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j == i)
		return (TRUE);
	return (FALSE);
}
