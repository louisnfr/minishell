/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:09:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 23:43:18 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_builtin(char *cmd)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	builtins[7] = NULL;

	i = -1;
	while (builtins[++i])
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtins[i]);
	return (NULL);
}

void	parse(char *input)
{
	char	**cmd;
	int		i;

	cmd = ft_split(input, 32);
	i = -1;
	// while (cmd[++i])
	// 	cmd[i] = ft_strtrim(cmd[i], "\"");
	free(input);
	exec(cmd);
	free_split(cmd);
}
