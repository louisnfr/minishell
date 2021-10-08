/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delimiters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:19 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/08 12:00:52 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_delimiter(int j, char *str, int delimiter)
{
	int	ret ;

	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j && str[j] && str[j] == delimiter)
	{
		if (str[j + 1] == delimiter)
			return (display_error_msg_delimiter(2, str[j]));
		return (display_error_msg_delimiter(1, str[j]));
	}
	ret = is_other_delimiter(str[j], str[j + 1], delimiter);
	if (ret == 1)
		return (display_error_msg_delimiter(1, str[j]));
	if (ret == 2)
		return (display_error_msg_delimiter(2, str[j]));
	return (1);
}

int	check_delimiter(char *str, char delimiter, int *i, int *words)
{
	int	count;
	int	j;

	count = 0;
	if (!str[*i] || (str[*i] && str[*i] != delimiter))
		return (1);
	(*words)++;
	while (str[*i] && str[*i] == delimiter)
	{
		(*i)++;
		count++;
	}
	if ((delimiter == '|' && count == 3) || (delimiter == '&' && count == 3))
		return (display_error_msg_delimiter(1, delimiter));
	if ((delimiter == '|' && count > 3) || (delimiter == '&' && count > 3)
		|| (delimiter == ';' && count > 1))
		return (display_error_msg_delimiter(2, delimiter));
	j = *i;
	return (check_error_delimiter(j, str, delimiter));
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
