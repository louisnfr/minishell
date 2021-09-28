/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:09:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 19:34:58 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

int	is_builtin(char *cmd)
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
			return (1);
	return (0);
	// return commande trouvee?
}

void	exec(char **cmd)
{
	if (is_builtin(cmd[0]))
	{
		printf("builtin cmd\n");
		ch_dir(cmd);
	}
	else
	{
		// execve in child
		printf("not builtin cmd\n");
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
