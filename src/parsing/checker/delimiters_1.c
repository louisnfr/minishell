/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/23 17:23:09 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_return(char *delimiters, int ret_value)
{
	free(delimiters);
	return (ret_value);
}

int	check_multiple_delimiters(char *str, int j, t_data *data)
{
	int		i;
	char	*delimiters;

	delimiters = safe_strdup("|&;<>", data);
	i = -1;
	while (delimiters[++i])
	{
		if (str[j] && str[j] == delimiters[i]
			&& delimiters[i] != '<' && delimiters[i] != '>')
		{
			if (str[j + 1] && str[j + 1] == delimiters[i])
				return (free_and_return(delimiters, 2));
			return (free_and_return(delimiters, 1));
		}
	}
	free(delimiters);
	if (str[j] == '<')
		return (check_left_marks(str, j));
	if (str[j] == '>')
		return (check_right_marks(str, j));
	return (0);
}

int	check_error_delimiter(int j, char *str, int delimiter, t_data *data)
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

int	check_error_count(
	char next, char delimiter, int count, t_bool is_beginning)
{
	if ((delimiter == '|' && count == 3 && !is_beginning)
		|| (delimiter == '&'
			&& ((count == 1 && next != '1') || count == 3) && !is_beginning)
		|| (delimiter == '>' && count == 3) || (delimiter == '<' && count == 3)
		|| ((delimiter == '(' || delimiter == ')') && count > 1))
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

int	check_delimiter(char *str, char delimiter, int *words, t_data *data)
{
	int		count;
	t_bool	is_beginning;
	int		ret;

	count = 0;
	if (!str || data->i >= ft_strlen(str) || !str[data->i]
		|| (str[data->i] && str[data->i] != delimiter))
		return (SUCCESS);
	(*words)++;
	is_beginning = check_beginning(str, data->i);
	while (str[data->i] && str[data->i] == delimiter)
	{
		data->i++;
		count++;
	}
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
