/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:55 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 01:33:17 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*new_cmd(char *cmd, int num)
{
	t_history	*ncmd;

	ncmd = malloc(sizeof(t_history));
	if (!ncmd)
		return (NULL);
	ncmd->num = num;
	ncmd->cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	ncmd->new = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!ncmd->cmd || !ncmd->new)
		return (NULL);
	strcpy(ncmd->cmd, cmd);
	strcpy(ncmd->new, cmd);
	ncmd->next = NULL;
	ncmd->previous = NULL;
	return (ncmd);
}

t_history	*getlast(t_history *hist)
{
	if (!hist)
		return (NULL);
	while (hist->next)
		hist = hist->next;
	return (hist);
}

void	add_cmd(t_history **hist, t_history *new)
{
	if (!*hist)
		*hist = new;
	else
	{
		new->next = *hist;
		(*hist)->previous = new;
		*hist = new;
	}
}

char	*find_cmd_history(t_history *hist, int h_num)
{
	while (hist)
	{
		if (hist->num == h_num)
		{
			if (strcmp(hist->cmd, hist->new))
				return (hist->new);
			return (hist->cmd);
		}
		hist = hist->next;
	}
	return (NULL);
}

void	print_history(t_history *hist)
{
	int	i;

	i = 1;
	hist = getlast(hist);
	while (hist)
	{
		printf("%5d  %s\n", i, hist->cmd);
		hist = hist->previous;
		i++;
	}
}

void	insert_char_history(
	t_history *hist, unsigned int cx, char c, int search)
{
	while (hist)
	{
		if (hist->num == search)
			break ;
		hist = hist->next;
	}
	hist->new = insert_char(hist->new, cx, c);
}

void	del_char_history(t_history *hist, unsigned int cx, int search)
{
	while (hist)
	{
		if (hist->num == search)
			break ;
		hist = hist->next;
	}
	delete_char(hist->new, cx - 1);
}

void	clear_hist(t_history *hist, int search)
{
	while (hist)
	{
		if (hist->new && hist->num == search)
		{
			free(hist->new);
			hist->new = malloc(sizeof(char) * (ft_strlen(hist->cmd) + 1));
			strcpy(hist->new, hist->cmd);
		}
		hist = hist->next;
	}
}

char	*insert_char(char *s, unsigned int cx, char c)
{
	if (s)
	{
		s = realloc(s, sizeof(char) * (ft_strlen(s) + 2));
		memmove(&s[cx + 1], &s[cx], ft_strlen(s) - cx + 1);
		s[cx] = c;
	}
	else
	{
		s = malloc(sizeof(char) * 2);
		s[0] = c;
		s[1] = 0;
	}
	return (s);
}

void	delete_char(char *s, unsigned int cx)
{
//	if (cx < 0 || cx > ft_strlen(s)) Problem compilation ggc
	if (cx > ft_strlen(s))
		return ;
	memmove(&s[cx], &s[cx + 1], ft_strlen(s) - cx);
}
