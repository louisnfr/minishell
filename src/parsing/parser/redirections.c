/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/23 15:16:06 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_files(int length, t_cmd *cmd_list, t_data *data)
{
	cmd_list->redirection = (int *)ft_calloc(1, sizeof(int) * length);
	if (!cmd_list->redirection)
		exit_error_bool("malloc()", data);
	cmd_list->files = (char **)ft_calloc(1, sizeof(char *) * (length + 1));
	if (!cmd_list->files)
		exit_error_bool("malloc()", data);
}

void	get_length_redir(char **argv, t_cmd *cmd_list, t_data *data)
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
			return ;
		if (redirection != HEREDOC)
			length++;
		i++;
		if (argv[i] && str_is_equal(argv[i], "2>&1"))
			i++;
	}
	if (length)
		malloc_files(length, cmd_list, data);
}

void	check_output_error(char **argv, t_cmd *cmd_list, t_data *data)
{
	if (argv[data->i] && str_is_equal(argv[data->i], "2>&1"))
	{
		cmd_list->redir_error = TRUE;
		data->i++;
	}
}

void	parse_redirections(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	redirection;
	int	j;

	redirection = 0;
	parse_redirections_heredoc(argv, cmd_list, data);
	get_length_redir(argv, cmd_list, data);
	j = 0;
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redirection = get_redirection(argv[data->i]);
		data->i++;
		if (!argv[data->i])
			return ;
		if (redirection != HEREDOC)
		{
			cmd_list->files[j] = safe_strdup(argv[data->i], data);
			cmd_list->redirection[j++] = redirection;
		}
		data->i++;
		check_output_error(argv, cmd_list, data);
	}
	if (cmd_list->files)
		cmd_list->files[j] = NULL;
}
