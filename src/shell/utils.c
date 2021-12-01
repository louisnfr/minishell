/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:03:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/30 23:29:20 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(int c)
{
	return (c == ' ' || c == '/' || c == ';' || c == '"');
}

char	*selected_input(t_confg *sh)
{
	if (sh->h_num == sh->search)
		return (sh->current);
	else
		return (sh->input);
}

void	clear_prompt(int cx, int k)
{
	int	i;

	i = -1;
	(void)k;
	while (++i < cx)
		write(1, "\x1b[1D", 4);
	write(1, "\x1b[0K", 4);
}

int	get_cut_pos(t_confg *sh)
{
	char	*input;
	int		i;

	input = selected_input(sh);
	i = sh->cx - 1;
	while (i && !is_sep(input[i - 1]))
		i--;
	return (i);
}

char	*get_current_word(t_confg *sh, t_data *data)
{
	char	*input;
	char	*substr;
	int		i;

	input = selected_input(sh);
	if (!input || !ft_strlen(input))
		return (NULL);
	i = sh->cx - 1;
	while (i > 0 && !is_sep(input[i - 1]))
		i--;
	substr = safe_substr(input, i, sh->cx - i, data);
	return (substr);
}
