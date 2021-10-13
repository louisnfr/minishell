/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:07:19 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 05:41:46 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_key(int k)
{
	return (k & 0x1f);
}

void	clear_prompt(t_data *data)
{
	write(STDOUT_FILENO, "\x1b[2K", 4);
	write(STDOUT_FILENO, "\x1b[999D", 6);
	write(1, data->pr, ft_strlen(data->pr));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*d;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	d = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = 0;
	return (d);
}
