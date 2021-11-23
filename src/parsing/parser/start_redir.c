/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:46:12 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/23 17:53:51 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd_list_input(
	int fd, char *filename, t_cmd *cmd_list, t_data *data)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->input = fd;
	if (cmd_list->input == -1)
	{
		display_error_redir(
			cmd_list->error_output, filename, strerror(errno));
		data->ret_value = 1;
	}
	else if (!cmd_list->args)
	{
		cmd_list->args = (char **)ft_calloc(1, sizeof(char *) * 2);
		if (!cmd_list->args)
			exit_error_bool("malloc()", data);
		cmd_list->args[0] = safe_strdup(filename, data);
		cmd_list->args[1] = NULL;
	}
}

void	handle_start_left_redir(
	int *delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	int		fd;
	char	*filename;

	data->i++;
	filename = safe_strdup(argv[data->i], data);
	if (argv[data->i])
		fd = open(argv[data->i], O_RDONLY, 0644);
	if (!argv[++data->i])
		return ;
	if (is_delimiter(argv[data->i]))
		*delimiter = get_delimiter(argv[data->i++]);
	else if (str_is_equal(argv[data->i], "("))
		handle_parentheses(*delimiter, argv, data);
	else if (cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(0, argv, cmd_list, data);
	else
		handle_bin_cmd(0, argv, cmd_list, data);
	fill_cmd_list_input(fd, filename, cmd_list, data);
	clean_free(&filename);
}

void	fill_cmd_list_output(
	int fd, char *filename, t_cmd *cmd_list, t_data *data)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->output = fd;
	if (cmd_list->output == -1)
	{
		display_error_redir(
			cmd_list->error_output, filename, strerror(errno));
		data->ret_value = 1;
	}
	else if (!cmd_list->args)
	{
		cmd_list->args = (char **)ft_calloc(1, sizeof(char *) * 2);
		if (!cmd_list->args)
			exit_error_bool("malloc()", data);
		cmd_list->args[0] = safe_strdup(filename, data);
		cmd_list->args[1] = NULL;
	}
}

void	handle_start_right_redir(
	int *delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	int		fd;
	char	*filename;

	data->i++;
	filename = safe_strdup(argv[data->i], data);
	if (argv[data->i])
		fd = open(argv[data->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!argv[++data->i])
		return ;
	if (is_delimiter(argv[data->i]))
		*delimiter = get_delimiter(argv[data->i++]);
	// else if (is_redirection(argv[data->i]))
	// 	printf("argv[data->i] = %s\n", argv[data->i]);
	else if (str_is_equal(argv[data->i], "("))
		handle_parentheses(*delimiter, argv, data);
	else if (cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(0, argv, cmd_list, data);
	else
		handle_bin_cmd(0, argv, cmd_list, data);
	fill_cmd_list_output(fd, filename, cmd_list, data);
	clean_free(&filename);
}

/*
void	handle_start_right_redir(
	int *delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	int		fd;
	char	*filename;

	data->i++;
	filename = safe_strdup(argv[data->i], data);
	printf("filename = %s\n", filename);
	if (argv[data->i])
		fd = open(argv[data->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!argv[++data->i])
		return ;
	if (is_delimiter(argv[data->i]))
		*delimiter = get_delimiter(argv[data->i++]);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->output = fd;
	if (cmd_list->output == -1)
	{
		display_error_redir(
			cmd_list->error_output, filename, strerror(errno));
		data->ret_value = 1;
	}
	clean_free(&filename);
}
*/
