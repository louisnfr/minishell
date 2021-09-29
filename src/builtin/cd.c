/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:03:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/29 16:36:54 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(char **cmd)
{
	char	*p;
	char	*new_path;
	char	*tmp;

	if (!cmd[1])
		chdir(getenv("HOME"));
	else if (cmd[1][0] == '~')
	{
		p = ft_substr(cmd[1], 1, ft_strlen(cmd[1]));
		tmp = ft_strjoin(getenv("HOME"), p);
		free(p);
		printf("%s\n", tmp);
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(cmd[1]);
	new_path = getcwd(NULL, 0);
	set_env("PWD", new_path);
}
