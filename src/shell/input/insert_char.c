/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:45:42 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/10 02:32:46 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_char(char *s, int cx, char c)
{
	if (s)
	{
		s = ft_realloc(s, sizeof(char) * (ft_strlen(s) + 2));
		ft_memmove(&s[cx + 1], &s[cx], ft_strlen(s) - cx + 1);
		s[cx] = c;
	}
	else
	{
		s = (char *)ft_calloc(1, sizeof(char) * 2);
		if (!s)
			return (NULL);
		s[0] = c;
		s[1] = 0;
	}
	return (s);
}

void	insert_char_history(t_hist *hist, int cx, char c, int search)
{
	while (hist)
	{
		if (hist->num == search)
			break ;
		hist = hist->next;
	}
	hist->new = insert_char(hist->new, cx, c);
}
