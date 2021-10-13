/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/13 12:58:56 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_error_msg(char *filename, char *errno_msg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errno_msg, 2);
	ft_putchar_fd('\n', 2);
}

t_bool	is_file_name(char *file)
{
	if (file)
		return (SUCCESS);
	return (FAIL);
}

void	handle_redirection(
	int redirection, char **argv, t_cmd *cmd_list, t_data *data)
{
	if (redirection == RIGHT_MARK)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->output = open(argv[data->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd_list->output == -1)
				display_error_msg(argv[data->i], strerror(errno));
		}
	}
	if (redirection == DOUBLE_RIGHT_MARK)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->output = open(argv[data->i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd_list->output == -1)
				display_error_msg(argv[data->i], strerror(errno));
		}
	}
	if (redirection == LEFT_MARK)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->input = open(argv[data->i], O_RDONLY);
			if (cmd_list->input == -1)
				display_error_msg(argv[data->i], strerror(errno));
		}
	}
	if (redirection == HEREDOC)
	{
		cmd_list->heredoc = ft_strdup("heredoc");
	//	printf("delimiter = %s\n", argv[data->i]);
		cmd_list->heredoc_delimiter = ft_strdup(argv[data->i]);
		read_heredoc(cmd_list, data);
		cmd_list->input = open(cmd_list->heredoc, O_RDONLY);
		if (cmd_list->input == -1)
			display_error_msg(cmd_list->heredoc, strerror(errno));
	}
}

void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;

	if (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		cmd_list->redirection = redirection;
		data->i++;
		handle_redirection(redirection, argv, cmd_list, data);
		data->i++;
	}
}
