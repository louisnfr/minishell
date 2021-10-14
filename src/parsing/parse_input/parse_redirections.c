/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/14 19:37:49 by efrancon         ###   ########.fr       */
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

char	*parse_heredoc_delimiter(char *delimiter, t_bool *quotes)
{
	char	*new_delimiter;
	int		i;
	char	charset;
	int		j;

	if (!delimiter || !delimiter[0]
		|| (delimiter[0] && delimiter[0] != '\"' && delimiter[0] != '\''))
		return (delimiter);
	charset = delimiter[0];
	new_delimiter = NULL;
	i = 0;
	j = 0;
	while (delimiter[++i] && delimiter[i] != charset)
		j++;
	new_delimiter = (char *)malloc(sizeof(char) * (j + 1));
	if (!new_delimiter)
		return (NULL);
	i = 1;
	j = 0;
	while (delimiter[i] && delimiter[i] != charset)
		new_delimiter[j++] = delimiter[i++];
	new_delimiter[j] = '\0';
	*quotes = 1;
	clean_free(&delimiter);
	return (new_delimiter);
}

void	redir_heredoc(char **argv, t_cmd *cmd_list, t_data *data)
{
	t_bool	quotes;

	quotes = 0;
	cmd_list->heredoc = ft_strdup("heredoc");
	if (!argv[data->i])
		return ;
	cmd_list->heredoc_delimiter = parse_heredoc_delimiter(
		ft_strdup(argv[data->i]), &quotes);
	read_heredoc(cmd_list, data, quotes);
	cmd_list->input = open(cmd_list->heredoc, O_RDONLY);
	if (cmd_list->input == -1)
		display_error_msg(cmd_list->heredoc, strerror(errno));
	unlink(cmd_list->heredoc);
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
		redir_heredoc(argv, cmd_list, data);
	if (redirection == ERROR)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->error_output = open(argv[data->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd_list->error_output == -1)
				display_error_msg(argv[data->i], strerror(errno));
		}
	}	
	if (redirection == DOUBLE_ERROR)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->error_output = open(argv[data->i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd_list->error_output == -1)
				display_error_msg(argv[data->i], strerror(errno));
		}
	}
	if (redirection == ERROR_AND_STDOUT)
		cmd_list->error_output = cmd_list->output;
}

void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;

	if (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		cmd_list->redirection = redirection;
		data->i++;
		if (!argv[data->i])
			return ;
		handle_redirection(redirection, argv, cmd_list, data);
		data->i++;
	}
}