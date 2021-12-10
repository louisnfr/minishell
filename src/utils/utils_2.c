/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 02:39:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/10 02:39:28 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_raw_input(char *input)
{
	int	i;

	if (str_is_only_char(input, ' '))
		return (FAIL);
	i = 0;
	while (input[i] == 32)
		i++;
	if (input[i] == '#')
		return (FAIL);
	return (SUCCESS);
}

int	count_slash(char *cwd, int *slash_count)
{
	int	i;

	i = ft_strlen(cwd);
	while (i >= 0 && *slash_count < 3)
	{
		if (cwd[i] == '/')
			(*slash_count)++;
		i--;
	}
	return (i);
}

int	check_gnl(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (!str[i] || !ft_isprint(str[i]))
			return (FAIL);
	}
	return (SUCCESS);
}

int	ctrl_key(int k)
{
	return (k & 0x1f);
}
