/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:35:38 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/28 20:58:54 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_and_return(char *delimiters, int ret_value)
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
