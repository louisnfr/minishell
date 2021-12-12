/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:45:55 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 18:10:05 by lraffin          ###   ########.fr       */
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

	if (!(**str) || !(ft_strchr(*str, '\'') || ft_strchr(*str, '\"')))
		return (SUCCESS);
	length = get_length(str, '\'', data);
	strs[++(*i)] = (char *)ft_calloc(1, sizeof(char) * (length + 2));
	if (!strs[*i])
		exit_error_str(NULL, "malloc()", data); // leaks non verifie
	fill_strs('\'', i, str, strs);
	return (SUCCESS);
}
