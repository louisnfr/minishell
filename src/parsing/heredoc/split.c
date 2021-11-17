/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:45:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 14:13:06 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_length(char **str, char charset, t_data *data)
{
	int		j;
	char	*tmp;

	j = 1;
	tmp = safe_strdup(*str, data);
	while (tmp[j] && tmp[j] != charset)
		j++;
	clean_free(&tmp);
	return (j);
}

static void	fill_strs(char charset, int *i, char **str, char **strs)
{
	int	j;

	j = 0;
	strs[*i][j++] = **str;
	(*str)++;
	while (**str)
	{
		strs[*i][j++] = **str;
		(*str)++;
		if (**str && **str == charset)
		{
			strs[*i][j++] = **str;
			break ;
		}
	}
	strs[*i][j] = '\0';
}

t_bool	handle_heredoc_quotes(int *i, char **str, char **strs, t_data *data)
{
	int		length;
	char	charset;

	while (**str && ft_isspace(**str))
		(*str)++;
	if (!(**str) || (**str && **str != '\'' && **str != '\"'))
		return (SUCCESS);
	charset = **str;
	length = get_length(str, charset, data);
	strs[++(*i)] = (char *)ft_calloc(1, sizeof(char) * (length + 2));
	if (!strs[*i])
		return (exit_error_bool("malloc()", data));
	fill_strs(charset, i, str, strs);
	return (SUCCESS);
}
