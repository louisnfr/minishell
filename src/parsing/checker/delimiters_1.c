/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/11 17:54:16 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_multiple_delimiters(char *str, int j)
{
	int		i;
	char	*delimiters;

	delimiters = ft_strdup("|&;<>");
	i = -1;
	while (delimiters[++i])
	{
		if (str[j] && str[j] == delimiters[i]
			&& delimiters[i] != '<' && delimiters[i] != '>')
		{
			if (str[j + 1] && str[j + 1] == delimiters[i])
			{
				free(delimiters);
				return (2);
			}
			free(delimiters);
			return (1);
		}
	}
	free(delimiters);
	if (str[j] == '<')
		return (check_left_marks(str, j));
	if (str[j] == '>')
		return (check_right_marks(str, j));
	return (0);
}

int	check_error_delimiter(int j, char *str, int delimiter)
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
	ret = check_multiple_delimiters(str, j);
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

int	check_delimiter(char *str, char delimiter, int *i, int *words)
{
	int		count;
	t_bool	is_beginning;
	int		ret;

	count = 0;
	if (!str || *i >= ft_strlen(str) || !str[*i]
		|| (str[*i] && str[*i] != delimiter))
		return (SUCCESS);
	(*words)++;
	is_beginning = check_beginning(str, i);
	while (str[*i] && str[*i] == delimiter)
	{
		(*i)++;
		count++;
	}
	if (!check_error_count(str[*i], delimiter, count, is_beginning))
		return (FAIL);
	ret = check_error_delimiter(*i, str, delimiter);
	if (ret == 2)
	{
		(*words)--;
		return (SUCCESS);
	}
	return (ret);
}
