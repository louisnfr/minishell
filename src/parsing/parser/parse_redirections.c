/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/20 16:59:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_msg_redir(int fd, char *filename, char *errno_msg)
{
	ft_putstr_fd("bash: ", fd);
	ft_putstr_fd(filename, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(errno_msg, fd);
	ft_putchar_fd('\n', fd);
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
	new_delimiter = (char *)ft_calloc(1, sizeof(char) * (j + 1));
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

void	redir_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	t_bool	quotes;

	quotes = 0;
	cmd_list->heredoc = ft_strjoin(get_env("HOME", data->env), "/heredoc");
	if (!argv[*j])
		return ;
	cmd_list->heredoc_delimiter = parse_heredoc_delimiter(
		ft_strdup(argv[*j]), &quotes);
	read_heredoc(cmd_list, data, quotes);
	cmd_list->input = open(cmd_list->heredoc, O_RDONLY);
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
				display_error_msg_redir(cmd_list->error_output, argv[data->i], strerror(errno));
		}
	}
	if (redirection == DOUBLE_RIGHT_MARK)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->output = open(argv[data->i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd_list->output == -1)
				display_error_msg_redir(cmd_list->error_output, argv[data->i], strerror(errno));
		}
	}
	if (redirection == LEFT_MARK)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->input = open(argv[data->i], O_RDONLY);
			if (cmd_list->input == -1)
				display_error_msg_redir(cmd_list->error_output, argv[data->i], strerror(errno));
		}
	}
	if (redirection == ERROR)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->error_output = open(argv[data->i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (cmd_list->error_output == -1)
				display_error_msg_redir(cmd_list->error_output, argv[data->i], strerror(errno));
		}
	}
	if (redirection == DOUBLE_ERROR)
	{
		if (is_file_name(argv[data->i]))
		{
			cmd_list->error_output = open(argv[data->i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd_list->error_output == -1)
				display_error_msg_redir(cmd_list->error_output, argv[data->i], strerror(errno));
		}
	}
	data->i++;
	if (argv[data->i] && str_is_equal(argv[data->i], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		data->i++;
	}
}

static void	handle_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	redir_heredoc(j, argv, cmd_list, data);
	(*j)++;
	if (argv[*j] && str_is_equal(argv[*j], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		(*j)++;
	}	
}

void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;
	int	j;
	
	j = data->i;
	redirection = 0;
	while (argv[j] && is_redirection(argv[j]))
	{
		redirection = get_redirection(argv[j]);
		j++;
		if (!argv[j])
			return ;
		if (redirection == HEREDOC)
			handle_heredoc(&j, argv, cmd_list, data);
		else
			j++;
	}
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		data->i++;
		if (!argv[data->i])
			return ;
		if (redirection != HEREDOC)
			handle_redirection(redirection, argv, cmd_list, data);
		else
			data->i++;
	}
	cmd_list->redirection = redirection;
}

/*
void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;

	if (!check_heredoc_proprity(argv, data))
		return ;
	redirection = 0;
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		cmd_list->redirection = redirection;
		data->i++;
		if (!argv[data->i])
			return ;
		handle_redirection(redirection, argv, cmd_list, data);
	}
}
*/
