/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:55 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:30:19 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hist	*new_cmd(char *cmd, int num)
{
	t_hist	*ncmd;

	ncmd = malloc(sizeof(t_hist));
	if (!ncmd)
		return (NULL);
	ncmd->num = num;
	ncmd->cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	ncmd->new = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!ncmd->cmd || !ncmd->new)
		return (NULL);
	ft_strcpy(ncmd->cmd, cmd);
	ft_strcpy(ncmd->new, cmd);
	ncmd->next = NULL;
	ncmd->previous = NULL;
	return (ncmd);
}

t_hist	*getlast(t_hist *hist)
{
	if (!hist)
		return (NULL);
	while (hist->next)
		hist = hist->next;
	return (hist);
}

void	add_cmd(t_hist **hist, t_hist *new)
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

char	*find_cmd_history(t_hist *hist, int h_num)
{
	while (hist)
	{
		if (hist->num == h_num)
		{
			if (ft_strcmp(hist->cmd, hist->new))
				return (hist->new);
			return (hist->cmd);
		}
		hist = hist->next;
	}
	return (NULL);
}

void	clear_hist(t_hist *hist, int search)
{
	while (hist)
	{
		if (hist->new && hist->num == search)
		{
			free(hist->new);
			hist->new = malloc(sizeof(char) * (ft_strlen(hist->cmd) + 1));
			if (hist->new)
				ft_strcpy(hist->new, hist->cmd);
		}
		hist = hist->next;
	}
}
