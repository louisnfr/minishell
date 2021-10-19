/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/14 16:54:46 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_delimiter(char *str)
{
	if (str_is_equal(str, "|"))
		return (PIPE);
	if (str_is_equal(str, "&&"))
		return (AND);
	if (str_is_equal(str, "||"))
		return (OR);
	if (str_is_equal(str, ";"))
		return (SEMICOLON);
	return (0);
}

t_bool	is_delimiter(char *str)
{
	return (str_is_equal(str, "&&")
		|| str_is_equal(str, ";")
		|| str_is_equal(str, "|")
		|| str_is_equal(str, "||"));
}

int	get_redirection(char *str)
{
	if (str_is_equal(str, "<"))
		return (LEFT_MARK);
	if (str_is_equal(str, "<<"))
		return (HEREDOC);
	if (str_is_equal(str, ">"))
		return (RIGHT_MARK);
	if (str_is_equal(str, ">>"))
		return (DOUBLE_RIGHT_MARK);
	if (str_is_equal(str, "2>"))
		return (ERROR);
	if (str_is_equal(str, "2>>"))
		return (DOUBLE_ERROR);
	if (str_is_equal(str, "2>&1"))
		return (ERROR_AND_STDOUT);
	return (0);
}

t_bool	is_redirection(char *str)
{
	return (str_is_equal(str, "<")
		|| str_is_equal(str, "<<")
		|| str_is_equal(str, ">")
		|| str_is_equal(str, ">>")
		|| str_is_equal(str, "2>")
		|| str_is_equal(str, "2>>")
		|| str_is_equal(str, "2>&1"));
}

t_bool	cmd_is_builtin(char *cmd)
{
	int		i;
	char	*builtins[9];

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	builtins[7] = "history";
	builtins[8] = NULL;
	i = -1;
	while (builtins[++i])
	{
		if (str_is_equal(cmd, builtins[i]))
			return (TRUE);
	}
	return (FALSE);
}