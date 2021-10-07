/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:25 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 17:39:25 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset_split(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == ';');
}

int	is_delimiter_split(char c)
{
	return (c == '&' || c == '|' || c == ';');
}

int	check_multiple_delimiters(
	char c1, char c2, char delimiter1, char delimiter2)
{
	if (c1 == delimiter1)
	{
		if (c2 == delimiter1)
			return (2);
		return (1);
	}
	if (c1 == delimiter2)
	{
		if (c2 == delimiter2)
			return (2);
		return (1);
	}
	return (0);
}

int	is_other_delimiter(char c1, char c2, char delimiter)
{
	if (delimiter == '|')
		return (check_multiple_delimiters(c1, c2, '&', ';'));
	if (delimiter == '&')
		return (check_multiple_delimiters(c1, c2, '|', ';'));
	if (delimiter == ';')
		return (check_multiple_delimiters(c1, c2, '|', '&'));
	return (0);
}

int	display_error_msg_delimiter(int count, char delimiter)
{
	if (count == 1)
		printf("bash: syntax error near unexpected token `%c'\n", delimiter);
	else
		printf("bash: syntax error near unexpected token `%c%c'\n",
			delimiter, delimiter);
	return (0);
}
