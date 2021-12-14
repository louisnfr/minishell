/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:29 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 16:20:42 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_end_cmd(
	char **argv, t_cmd **cmd_list, t_data *data)
{
	if ((argv[data->i] && str_is_equal(argv[data->i], ")")) || (data->i > 1
			&& argv[data->i - 1] && str_is_equal(argv[data->i - 1], ")")
			&& (!argv[data->i] || !is_redirection(argv[data->i]))))
		return ;
	if (argv[data->i] && !is_delimiter(argv[data->i])
		&& !is_parenthese(argv[data->i]))
	{
		while (argv[data->i] && !is_delimiter(argv[data->i])
			&& !is_parenthese(argv[data->i]))
		{
			parse_redirections(argv, cmd_list, data);
			clean_redir(data);
			if (argv[data->i] && argv[data->i][0] == '-'
					&& !(*cmd_list)->is_builtin)
				(*cmd_list)->options = find_cmd_options_end(argv, data);
			if (argv[data->i] && !is_delimiter(argv[data->i]))
				(*cmd_list)->args = find_cmd_args_end(
						argv, (*cmd_list)->args, data);
		}
	}
	else
		parse_redirections(argv, cmd_list, data);
}

void	parse_cmd(int delimiter, char **argv, t_cmd **cmd_list, t_data *data)
{
	data->tmp_path = (*cmd_list)->path;
	data->tmp_cmd = (*cmd_list)->command;
	check_expansion_var(argv[data->i], data);
	if (argv[data->i] && str_is_equal(argv[data->i], "("))
		handle_parentheses(delimiter, argv, data);
	else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(delimiter, argv, *cmd_list, data);
	else if (argv[data->i] && !str_is_equal(argv[data->i], ")"))
		handle_bin_cmd(delimiter, argv, *cmd_list, data);
	data->tmp_path = NULL;
	data->tmp_cmd = NULL;
}

static void	parse_argv(char **argv, t_cmd *cmd_list, t_data *data)
{
	int		delimiter;

	delimiter = 0;
	data->redir = NULL;
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		clean_redir(data);
		if (argv[data->i] && is_redirection(argv[data->i]))
			data->redir = parse_start_redirection(argv, data);
		if (!argv[data->i] || (argv[data->i] && is_delimiter(argv[data->i])))
		{
			create_new_cmd(&cmd_list, data);
			parse_redirections(argv, &cmd_list, data);
			continue ;
		}
		parse_cmd(delimiter, argv, &cmd_list, data);
		parse_end_cmd(argv, &cmd_list, data);
	}
	clean_redir(data);
}

static char	**get_argv(char *input, t_data *data)
{
	char	**argv;

	input = check_input(input, data);
	if (!input)
		return (NULL);
	argv = split_input(input, data);
	if (!argv)
	{
		clean_free(&input);
		return (NULL);
	}
	argv = check_argv(input, argv, data);
	clean_free(&input);
	return (argv);
}

t_bool	parse(char *input, t_data *data)
{
	char	**argv;
	t_cmd	*cmd_list;

	if (!input)
		return (SUCCESS);
	cmd_list = data->cmd_list;
	argv = get_argv(input, data);
	if (!argv)
	{
		data->ret_value = 2;
		return (FAIL);
	}
	data->argv = &argv;
	data->i = 0;
	parse_argv(argv, cmd_list, data);
	free_double_str(argv);
	if (!data->heredoc_failed)
		parse_pipes(cmd_list, data);
	return (SUCCESS);
}
