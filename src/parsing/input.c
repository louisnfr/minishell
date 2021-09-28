/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:09:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 16:16:38 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

void	exec(char **cmd)
{
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

	if (!ft_strcmp(cmd[0], "exit"))
	{
		free_split(cmd);
		exit(EXIT_SUCCESS);
	}
}

void	parse(char *input)
{
	char	**cmd;

	cmd = ft_split(input, 32);
	free(input);
	exec(cmd);
	free_split(cmd);
}
