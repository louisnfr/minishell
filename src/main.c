/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/27 01:07:42 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	write(1, "minishell\033[1;32m$\033[0m ", 28);
}


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char	*input;

	while (1)
	{
		input = readline("minishell\033[1;32m$\033[0m ");
		if (!ft_strcmp(input, "exit"))
			exit(EXIT_SUCCESS);
		printf("%s\n", input);
		// prompt();
		// truc pour attendre
		// pourquoi gnl avant printf
		// if (takeInput(&input))
		// 	continue ;
		// if (get_next_line(0, &input))
		// 	continue ;
		// write(1, "test\n", 5);
	}

	return (0);
}
