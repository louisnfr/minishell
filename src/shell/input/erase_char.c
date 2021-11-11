/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:10 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 20:40:29 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_cmd_history(char *input, t_history *history, int search)
{
	int	i;

	i = ft_strlen(input);
	while (i)
		erase_char_history(history, i--, search);
}

void	erase_char_history(t_history *hist, int cx, int search)
{
	while (hist)
	{
		if (hist->num == search)
			break ;
		hist = hist->next;
	}
	erase_char(hist->new, cx - 1);
}

void	erase_char(char *s, int cx)
{
	if (cx > ft_strlen(s))
		return ;
	memmove(&s[cx], &s[cx + 1], ft_strlen(s) - cx);
}
