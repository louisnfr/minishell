/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:15:38 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/25 02:16:45 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(int status, int *exit_code)
{
	int	return_value;

	return_value = 0;
	if (WIFEXITED(status))
		return_value = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		return_value = WTERMSIG(status) + 128;
		if (return_value == 130)
			ft_putstr("\n");
		if (return_value == 131)
			ft_putstr("Quit (core dumped)\n");
	}
	*exit_code = return_value;
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
