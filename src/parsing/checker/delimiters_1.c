/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/28 21:04:12 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error_delimiter(int j, char *str, int delimiter, t_data *data)
{
	int		ret;

	if (delimiter == '(' || delimiter == ')')
		return (1);
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j && str[j] && str[j] == delimiter
		&& delimiter != '(' && delimiter != ')')
	{
		if (str[j + 1] == delimiter)
			return (display_error_msg_delimiter(2, str[j]));
		return (display_error_msg_delimiter(1, str[j]));
	}
	ret = check_multiple_delimiters(str, j, data);
	if ((ret > 0 && ret < 4) || ret == -1)
	{
		if (!is_error_redir(str, j))
			return (display_error_msg_delimiter(ret, str[j]));
		return (2);
	}
	return (1);
}

static int	check_error_count(
	char next, char delimiter, int count, t_bool is_beginning)
{
	if ((delimiter == '|' && count == 3 && !is_beginning) || (delimiter == '&'
			&& ((count == 1 && next != '1') || count == 3) && !is_beginning)
		|| (delimiter == '>' && count == 3) || (delimiter == '<' && count == 3))
		return (display_error_msg_delimiter(1, delimiter));
	if ((delimiter == '|' && count == 3) || (delimiter == '&' && count == 3)
		|| (delimiter == '|' && count > 3) || (delimiter == '&' && count > 3)
		|| (delimiter == ';' && count > 1) || (delimiter == '>' && count > 3)
		|| (delimiter == '<' && count == 4))
		return (display_error_msg_delimiter(2, delimiter));
	if (delimiter == '<' && count > 4)
		return (display_error_msg_delimiter(3, delimiter));
	return (SUCCESS);
}

static int	count_delimiter(char *str, char delimiter, t_data *data)
{
	int	count;

	count = 0;
	while (str[data->i] && str[data->i] == delimiter)
	{
		data->i++;
		count++;
		if (delimiter == '(' || delimiter == ')')
			break ;
	}
	return (count);
}

int	check_delimiter(char *str, char delimiter, int *words, t_data *data)
{
	int		count;
	t_bool	is_beginning;
	int		ret;

	if (!str || data->i >= ft_strlen(str) || !str[data->i]
		|| (str[data->i] && str[data->i] != delimiter))
		return (SUCCESS);
	(*words)++;
	is_beginning = check_beginning(str, data->i);
	count = count_delimiter(str, delimiter, data);
	if (!check_error_count(str[data->i], delimiter, count, is_beginning))
		return (FAIL);
	ret = check_error_delimiter(data->i, str, delimiter, data);
	if (ret == 2)
	{
		(*words)--;
		return (SUCCESS);
	}
	return (ret);
}
