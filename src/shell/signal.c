/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:15:38 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 16:00:04 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(int status, int *exit_code)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status) + 128;
		if (ret == 130)
			ft_putstr("\n");
		if (ret == 131)
			ft_putstr("Quit (core dumped)\n");
	}
	*exit_code = ret;
}

void	handle_sig(int sig)
{
	(void)sig;
}

void	init_signals(t_data *data)
{
	(void)data;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
