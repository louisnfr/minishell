/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 18:21:18 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

void	signal_handler(int signo)
{
	(void)signo;
	// if (SIGINT == signo)
	// {
		printf("slfksjd");
	// 	signal_handler(SIGINT);
	// }
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	create_env(envp);
	while (1)
	{
		prompt();
		// signal(SIGINT, signal_handler);
		get_next_line(0, &input);
		parse(input);
	}
	return (0);
}

/*
prompt
get input
parse input
execute
free
*/
