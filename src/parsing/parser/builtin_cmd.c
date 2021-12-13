/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:52:46 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 13:50:33 by efrancon         ###   ########.fr       */
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

static int	handle_quotes(char *quote, char first_char)
{
	if (first_char == '\'' || first_char == '\"')
	{
		*quote = first_char;
		return (2);
	}
	*quote = 0;
	return (1);
}

static t_bool	is_option_echo(char **argv, t_data *data)
{
	int		j;
	int		ret;
	char	quote;

	ret = FAIL;
	if (!argv)
		return (FAIL);
	while (argv[++data->i] && (argv[data->i][0] == '-'
		|| argv[data->i][0] == '\'' || argv[data->i][0] == '\"'))
	{
		j = handle_quotes(&quote, argv[data->i][0]);
		if (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
		{
			j++;
			while (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
				j++;
			if (argv[data->i][j] && argv[data->i][j] != quote)
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
				exit_error_strs(argv, "malloc()", data);
			cmd_list->options[0] = safe_strdup("-n", data);
			cmd_list->options[1] = NULL;
		}
	}
	cmd_list->is_builtin = TRUE;
	cmd_list->args = find_cmd_args(argv, data);
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
	if (argv[data->i] && argv[data->i][0] == '-')
		cmd_list->options = find_cmd_options_end(argv, data);
}
