/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/27 20:24:15 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

https://misc.flogisoft.com/bash/tip_colors_and_formatting

void	prompt(char **env)
{
	(void)env;
	ft_putstr_fd("minishell\033[1;32m$\033[0m ", 1);
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

	for(int q=0; env[q]; q++)
		printf("env[%d]: %s\n", q, env[q]);
	if (ac != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		prompt(env);
		get_next_line(0, &input);
		check(input);
	}
	return (0);
}
