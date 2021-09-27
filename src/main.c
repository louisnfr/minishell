/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/27 20:15:25 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	ft_putstr_fd("minishell\033[1;32m$\033[0m ", 1);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		prompt();
		// ft_putstr("\n");
		signal(SIGINT, signal_handler);
	}
}

void	check(char *input)
{
	if (!ft_strcmp(input, "exit"))
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*input;

	if (ac != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		prompt(env);
		get_next_line(0, &input);
		// signal(SIGINT, signal_handler);
		check(input);
	}
	return (0);
}
