/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/27 01:13:06 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	char	*input;

	if (ac != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline("minishell\033[1;32m$\033[0m ");
		if (!ft_strcmp(input, "exit"))
			exit(EXIT_SUCCESS);
		printf("cmd: %s\n", input);
	}
	return (0);
}
