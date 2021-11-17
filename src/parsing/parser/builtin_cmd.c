/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:52:46 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 15:47:46 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_bool	is_option_echo(char **argv, t_data *data)
{
	int	j;
	int	ret;

	ret = FAIL;
	if (!argv)
		return (FAIL);
	while (argv[++data->i] && argv[data->i][0] == '-')
	{
		j = 1;
		if (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
		{
			j++;
			while (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
				j++;
			if (argv[data->i][j])
				break ;
			ret = SUCCESS;
		}
		else
			break ;
	}
	data->i--;
	return (ret);
}

void	handle_builtin_cmd(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	create_new_cmd(&cmd_list, data);
	cmd_list->command = safe_strdup(argv[data->i], data);
	if (str_is_equal(cmd_list->command, "echo"))
	{
		if (is_option_echo(argv, data))
		{
			cmd_list->options = (char **)ft_calloc(1, sizeof(char *) * 2);
			if (!cmd_list->options)
				exit_error_bool("malloc()", data);
			cmd_list->options[0] = safe_strdup("-n", data);
			cmd_list->options[1] = NULL;
		}
	}
	cmd_list->is_builtin = TRUE;
	cmd_list->args = find_cmd_args(argv, data);
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
	parse_redirections(argv, cmd_list, data);
}
