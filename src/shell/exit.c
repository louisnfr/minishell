/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:23:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/28 12:09:51 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(const char *s, t_config *sh)
{
	if (errno == 0)
		write(2, s, ft_strlen(s));
	else
		perror(s);
	if (sh->init_termios)
		disable_raw_mode(sh);
	exit(EXIT_FAILURE);
}

void	exit_free(t_config *sh, t_history *hist)
{
	ft_putstr_fd("exit\n", 2);
	disable_raw_mode(sh);
	free_history(hist);
	free(sh);
	sh = NULL;
	hist = NULL;
	exit(0);
}

void	free_history(t_history *hist)
{
	t_history	*tmp;

	tmp = hist;
	while (tmp)
	{
		hist = hist->next;
		free(tmp->cmd);
		free(tmp->new);
		free(tmp);
		tmp = NULL;
		tmp = hist;
	}
	free(tmp);
	free(hist);
	hist = NULL;
}
