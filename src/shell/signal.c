/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:15:38 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/05 19:52:38 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig(int sig)
{
	(void)sig;
}

static void	ignore_signals(void)
{
	signal(SIGSEGV, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
}

void	handle_status(int status, int *exit_code)
{
	int	ret;

	ret = 0;
	ignore_signals();
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

void	init_signals(t_data *data)
{
	(void)data;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
