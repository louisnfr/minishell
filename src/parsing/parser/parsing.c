/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:29 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/25 15:43:15 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_argv(char *input, t_data *data)
{
	char	**argv;

	(void)data;
	input = check_input(input, data);
	if (!input)
		return (NULL);
	argv = split_input(input, data);
	if (!argv)
	{
		clean_free(&input);
		return (NULL);
	}
	argv = check_argv(argv, data);
	clean_free(&input);
	return (argv);
}

void	parse_argv(char **argv, t_cmd *cmd_list, t_data *data)
{
	int		delimiter;
	t_redir	*redir;

	delimiter = 0;
	redir = NULL;
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		clean_redir(&redir);
		if (argv[data->i] && is_redirection(argv[data->i]))
			redir = parse_start_redirection(argv, data);
		if (!argv[data->i] || (argv[data->i] && is_delimiter(argv[data->i])))
		{
			create_new_cmd(&cmd_list, data);
			parse_redirections(redir, argv, &cmd_list, data);
			continue ;
		}
		if (argv[data->i] && str_is_equal(argv[data->i], "("))
			handle_parentheses(delimiter, argv, data);
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
		else if (argv[data->i])
			handle_bin_cmd(delimiter, argv, cmd_list, data);
		if (argv[data->i] && !is_delimiter(argv[data->i]))
		{
			while (argv[data->i] && !is_delimiter(argv[data->i]))
			{
				parse_redirections(redir, argv, &cmd_list, data);
				clean_redir(&redir);
				if (argv[data->i] && argv[data->i][0] == '-')
					cmd_list->options = find_cmd_options_end(argv, data);
				if (argv[data->i] && !is_delimiter(argv[data->i]))
					cmd_list->args = find_cmd_args_end(
							argv, cmd_list->args, data);
			}
		}
		else
			parse_redirections(redir, argv, &cmd_list, data);
	}
	clean_redir(&redir);
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
	data->i = 0;
	parse_argv(argv, cmd_list, data);
	free_double_str(argv);
	parse_pipes(cmd_list, data);
	return (SUCCESS);
}

/*
void	parse_argv(char **argv, t_cmd *cmd_list, t_data *data)
{
	int		delimiter;

	delimiter = 0;
	if (argv[data->i] && str_is_equal(argv[data->i], "<"))
		handle_start_left_redir(&delimiter, argv, cmd_list, data);
	else if (argv[data->i] && str_is_equal(argv[data->i], ">"))
		handle_start_right_redir(&delimiter, argv, cmd_list, data);
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (argv[data->i] && str_is_equal(argv[data->i], "("))
			handle_parentheses(delimiter, argv, data);
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
		else if (argv[data->i])
			handle_bin_cmd(delimiter, argv, cmd_list, data);
	}
}
*/
