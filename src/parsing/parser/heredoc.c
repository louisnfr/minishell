/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:58:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/03 13:33:37 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_heredoc_delimiter(char *delimiter, t_data *data)
{
	char	*new_delimiter;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (delimiter[++i])
	{
		if (delimiter[i] != '\"' && delimiter[i] != '\'')
			j++;
	}
	new_delimiter = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!new_delimiter)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	i = -1;
	j = 0;
	while (delimiter[++i])
	{
		if (delimiter[i] != '\"' && delimiter[i] != '\'')
			new_delimiter[j++] = delimiter[i];
	}
	new_delimiter[j] = '\0';
	clean_free(&delimiter);
	return (new_delimiter);
}

static void	redir_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	t_bool	quotes;

	quotes = 0;
	if (!cmd_list->heredoc_delimiter && argv[*j])
	{
		cmd_list->heredoc_delimiter = safe_strdup(argv[*j], data);
		if (cmd_list->heredoc_delimiter
			&& (ft_strchr(cmd_list->heredoc_delimiter, '\"')
				|| ft_strchr(cmd_list->heredoc_delimiter, '\'')))
		{
			cmd_list->heredoc_delimiter = parse_heredoc_delimiter(
					cmd_list->heredoc_delimiter, data);
			quotes = 1;
		}
	}
	read_heredoc(quotes, &cmd_list, data);
}

void	handle_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	redir_heredoc(j, argv, cmd_list, data);
	(*j)++;
	if (argv[*j] && str_is_equal(argv[*j], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		(*j)++;
	}
}

void	parse_redirection_heredoc(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	j;
	int	redirection;

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
	if (data->pipe_heredoc)
	{
		safe_close_fd(data->pipe_heredoc[1], data);
		free(data->pipe_heredoc);
		data->pipe_heredoc = NULL;
	}
}
