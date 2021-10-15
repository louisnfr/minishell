/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:25 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/15 15:54:50 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset_split(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == ';' || c == '<'
		|| c == '>');
}

int	is_delimiter_split(char c)
{
	return (c == '&' || c == '|' || c == ';'|| c == '<' || c == '>');
}

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
	if (count > 0 && count < 4)
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
		return (-1);
	if (count == 3)
		return (1);
	if (count > 3)
		return (2);
	return (0);
}

int	check_multiple_delimiters(char *str, int j, t_data *data)
{
	int		i;
	char	*delimiters;

	delimiters = data->tab_delimiters;
	i = -1;
	while (delimiters[++i])
	{
		if (str[j] && str[j] == delimiters[i]
			&& delimiters[i] != '<' && delimiters[i] != '>')
		{
			if (str[j + 1] && str[j + 1] == delimiters[i])
				return (2);
			return (1);
		}
	}
	if (str[j] == '<')
		return (check_left_marks(str, j));
	if (str[j] == '>')
		return (check_right_marks(str, j));
	return (0);
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
