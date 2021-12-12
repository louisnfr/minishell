/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:36:06 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/12 19:58:13 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_arrow_key(char c)
{
	if (c == 'A')
		return (ARROW_UP);
	if (c == 'B')
		return (ARROW_DOWN);
	if (c == 'C')
		return (ARROW_RIGHT);
	if (c == 'D')
		return (ARROW_LEFT);
	return ('\x1b');
}

static int	read_escape_seq(void)
{
	char	seq[3];

	if ((read(STDIN_FILENO, &seq[0], 1) != 1)
		|| (read(STDIN_FILENO, &seq[1], 1) != 1))
		return ('\x1b');
	if (seq[0] == '[')
	{
		if (ft_isdigit(seq[1]))
		{
			if (read(STDIN_FILENO, &seq[2], 1) != 1)
				return ('\x1b');
			if (seq[2] == '~')
			{
				if (seq[1] == '3')
					return (DELETE);
			}
		}
		return (read_arrow_key(seq[1]));
	}
	return ('\x1b');
}

int	read_key(t_confg *sh, t_data *data)
{
	int		ret;
	char	c;

	(void)sh;
	while (1)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret == -1 && errno != EAGAIN)
			exit_error_str(NULL, "read()", data);
		if (ret == 1)
			break ;
	}
	if (c == '\x1b')
		return (read_escape_seq());
	else
		return (c);
}
