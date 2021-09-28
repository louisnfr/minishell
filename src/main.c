/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 15:32:54 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}

void	extract(char *input)
{
	char	**cmd;
	// char	*tmp;

	cmd = ft_split(input, 32);

	if (!ft_strcmp(cmd[0], "/bin/ls"))
	{
		execve(cmd[0], cmd, g_env);
		// quitte le process
	}

	if (!ft_strcmp(cmd[0], "cd"))
	{
		if (!cmd[1])
			chdir(get_env("HOME"));
		else
			chdir(cmd[1]);
	}

	if (!ft_strcmp(input, "exit"))
	{
		free(input);
		free_split(cmd);
		exit(EXIT_SUCCESS);
	}
	free_split(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)av;
	g_env = env;
	if (ac != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		extract(input);
		free(input);
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
