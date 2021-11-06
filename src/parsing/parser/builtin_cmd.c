/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:52:46 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/05 14:52:47 by efrancon         ###   ########.fr       */
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
	char	*command;
	char	**options;
	char	**args;

	options = NULL;
	args = NULL;
	command = ft_strdup(argv[data->i]);
	if (str_is_equal(command, "echo"))
	{
		if (is_option_echo(argv, data))
		{
			options = (char **)ft_calloc(1, sizeof(char *) * 2);
			options[0] = ft_strdup("-n");
			options[1] = NULL;
		}
	}
	create_new_cmd(command, options, NULL, &cmd_list);
	cmd_list->is_builtin = TRUE;
	args = find_cmd_args(argv, data);
	cmd_list->args = args;
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
	parse_redirections(argv, cmd_list, data);
}
