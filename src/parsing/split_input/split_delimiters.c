/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:19 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/15 15:52:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_error_redir(char *str, int j)
{
	int	i;
	
	i = 0;
	if (j < 2)
		return (FAIL);
	if ((str[j - 2] && str[j - 2] == '2') && (str[j - 1] && str[j - 1] == '>')
		&& (str[j + 1] && str[j + 1] == '1'))
		return (TRUE);
	return (FAIL);
}

int	check_error_delimiter(int j, char *str, int delimiter, t_data *data)
{
	int		ret;

	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j && str[j] && str[j] == delimiter)
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

t_bool	check_beginning(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j == *i)
		return (TRUE);
	return (FALSE);
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

int	check_delimiter(char *str, char delimiter, int *i, int *words, t_data *data)
{
	int		count;
	int		j;
	t_bool	is_beginning;
	int		ret;
	count = 0;
	if (!str[*i] || (str[*i] && str[*i] != delimiter))
		return (1);
	(*words)++;
	is_beginning = check_beginning(str, i);
	while (str[*i] && str[*i] == delimiter)
	{
		(*i)++;
		count++;
	}
	if ((delimiter == '|' && count == 3 && !is_beginning)
		|| (delimiter == '&' && count == 3 && !is_beginning) ||
		(delimiter == '>' && count == 3) || (delimiter == '<' && count == 3))
		return (display_error_msg_delimiter(1, delimiter));
	if ((delimiter == '|' && count == 3) || (delimiter == '&' && count == 3)
		|| (delimiter == '|' && count > 3) || (delimiter == '&' && count > 3)
		|| (delimiter == ';' && count > 1) || (delimiter == '>' && count > 3)
		|| (delimiter == '<' && count == 4))
		return (display_error_msg_delimiter(2, delimiter));
	if (delimiter == '<' && count > 4)
		return (display_error_msg_delimiter(3, delimiter));
	j = *i;
	ret = check_error_delimiter(j, str, delimiter, data);
	if (ret == 2)
	{
		(*words)--;
		return (SUCCESS);
	}
	return (ret);
}

int	handle_delimiters(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp && tmp[j] && is_charset_split(tmp[j]))
		j++;
	free(tmp);
	tmp = NULL;
	strs[i] = (char *)malloc(sizeof(char) * (j + 1));
	if (!strs[i])
		return (0);
	j = 0;
	while (**str && is_delimiter_split(**str))
	{
		strs[i][j++] = **str;
		(*str)++;
	}
	strs[i][j] = '\0';
	return (1);
}
