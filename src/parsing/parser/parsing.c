/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:29 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/16 13:25:09 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_start_redir(char **argv, t_cmd *cmd_list, t_data *data)
{
	int		fd;
	char	*filename;

	data->i++;
	filename = safe_strdup(argv[data->i], data);
	if (argv[data->i])
		fd = open(argv[data->i], O_RDONLY);
	if (!argv[++data->i])
		return ;
	if (cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(0, argv, cmd_list, data);
	else
		handle_bin_cmd(0, argv, cmd_list, data);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->redirection = LEFT_MARK;
	cmd_list->input = fd;
	if (cmd_list->input == -1)
		display_error_redir(
			cmd_list->error_output, filename, strerror(errno));
	clean_free(&filename);
}

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

	delimiter = 0;
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
	if (argv[data->i] && str_is_equal(argv[data->i], "<"))
		handle_start_redir(argv, cmd_list, data);
	parse_argv(argv, cmd_list, data);
	free_double_str(argv);
	parse_pipes(cmd_list, data);
	return (SUCCESS);
}
