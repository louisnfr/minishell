/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 20:13:01 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_length_redir(
	char **argv, t_cmd *cmd_list, t_data *data)
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
	return (malloc_files(argv, length, cmd_list, data));
}

static void	check_output_error(char **argv, t_cmd *cmd_list, t_data *data)
{
	if (argv[data->i] && str_is_equal(argv[data->i], "2>&1"))
	{
		cmd_list->redir_error = TRUE;
		data->i++;
	}
}

static void	loop_redir(int j, char **argv, t_cmd **cmd_list, t_data *data)
{
	int		redirection;

	redirection = 0;
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		data->i++;
		if (!argv[data->i])
			break ;
		if (redirection != HEREDOC)
		{
			(*cmd_list)->files[j] = safe_strdup(argv[data->i], data);
			(*cmd_list)->redirection[j++] = redirection;
		}
		data->i++;
		check_output_error(argv, *cmd_list, data);
	}
	if ((*cmd_list)->files && j > 0)
		(*cmd_list)->files[j] = NULL;
}

void	parse_redirections(
	char **argv, t_cmd **cmd_list, t_data *data)
{
	int		j;
	char	**existing_files;
	int		*existing_redir;

	if (!data->redir && !argv[data->i])
		return ;
	existing_redir = NULL;
	while (*cmd_list && (*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	existing_files = copy_existing_files(
			argv, &existing_redir, *cmd_list, data);
	j = get_length_redir(argv, *cmd_list, data);
	start_heredoc_case(j, argv, cmd_list, data);
	parse_redirection_heredoc(argv, *cmd_list, data);
	if (existing_files && existing_redir)
		fill_existing_files_redir(
			existing_redir, existing_files, *cmd_list, data);
	loop_redir(j, argv, cmd_list, data);
	if (existing_files)
		free_double_str(existing_files);
	if (existing_redir)
		free(existing_redir);
}
