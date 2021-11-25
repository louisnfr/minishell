/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:15:38 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/25 01:48:34 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	//output 130
	write(1, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	//output 131
	write(1, "Quit: 3\n", 8);
}

void	init_signals(t_data *data)
{
	(void)data;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
