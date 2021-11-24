/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/24 16:29:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_files(int length, t_redir *redir, t_cmd *cmd_list, t_data *data)
{
	int	i;

	if (!length && !redir)
		return ;
	if (redir)
		length += redir->count;
	cmd_list->redirection = (int *)ft_calloc(1, sizeof(int) * length);
	if (!cmd_list->redirection)
		exit_error_bool("malloc()", data);
	cmd_list->files = (char **)ft_calloc(1, sizeof(char *) * (length + 1));
	if (!cmd_list->files)
		exit_error_bool("malloc()", data);
	if (redir)
	{
		i = -1;
		while (redir->files[++i])
		{
			cmd_list->redirection[i] = redir->redirection[i];
			cmd_list->files[i] = safe_strdup(redir->files[i], data);
		}
	}
}

int	get_length_redir(
	t_redir *redir, char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;
	int	length;
	int	i;

	redirection = 0;
	length = 0;
	i = data->i;
	while (argv[i] && is_redirection(argv[i]))
	{
		redirection = get_redirection(argv[i]);
		i++;
		if (!argv[i])
			break ;
		if (redirection != HEREDOC)
			length++;
		i++;
		if (argv[i] && str_is_equal(argv[i], "2>&1"))
			i++;
	}
	malloc_files(length, redir, cmd_list, data);
	if (redir)
		return (redir->count);
	return (0);
}

void	check_output_error(char **argv, t_cmd *cmd_list, t_data *data)
{
	if (argv[data->i] && str_is_equal(argv[data->i], "2>&1"))
	{
		cmd_list->redir_error = TRUE;
		data->i++;
	}
}

void	get_filename(int k, char *str, t_cmd **cmd_list, t_data *data)
{
	char	quote;
	int		i;
	int		j;

	if (str && (str[0] == '\'' || str[0] == '\"'))
	{
		quote = str[0];
		i = 0;
		j = 0;
		while (str[++i] && str[i] != quote)
			j++;
		(*cmd_list)->files[k] = (char *)ft_calloc(1, sizeof(char) * (j + 1));
		if (!(*cmd_list)->files[k])
			exit_error_void(NULL, "malloc()", data);
		i = 1;
		j = 0;
		while (str[i] && str[i] != quote)
			(*cmd_list)->files[k][j++] = str[i++];
		(*cmd_list)->files[k][j] = '\0';
	}
	else
		(*cmd_list)->files[k] = safe_strdup(str, data);
}

void	parse_redirections(
	t_redir *redir, char **argv, t_cmd **cmd_list, t_data *data)
{
	int	redirection;
	int	j;

	redirection = 0;
	parse_redirections_heredoc(argv, *cmd_list, data);
	while (*cmd_list && (*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	j = get_length_redir(redir, argv, *cmd_list, data);
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		data->i++;
		if (!argv[data->i])
			break ;
		if (redirection != HEREDOC)
		{
			get_filename(j, argv[data->i], cmd_list, data);
			(*cmd_list)->redirection[j++] = redirection;
		}
		data->i++;
		check_output_error(argv, *cmd_list, data);
	}
	if ((*cmd_list)->files)
		(*cmd_list)->files[j] = NULL;
	if (argv[data->i] && argv[data->i][0] == '-')
		(*cmd_list)->options = find_cmd_options_end(argv, data);
}
