/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:15:38 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/07 02:49:47 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig(int sig)
{
	(void)sig;
}

void	handle_status(int sig, int *exit_code)
{
	const char	*signums[] = {
	[SIGINT] = "\n",
	[SIGSEGV] = "Segmentation fault\n",
	[SIGABRT] = "Abort\n",
	[SIGQUIT] = "Quit\n",
	[SIGTRAP] = "Trace/Breakpoint Trap\n",
	[SIGBUS] = "Bus Error\n",
	};

	if (signums[sig])
		ft_putstr_fd((char *)signums[sig], STDERR_FILENO);
	*exit_code = (sig + 128);
}

void	init_signals(t_data *data)
{
	(void)data;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
