/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:46:12 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 13:18:58 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_redir(t_data *data)
{
	if (data->redir)
	{
		free_double_str(data->redir->files);
		if (data->redir->redirection)
		{
			free(data->redir->redirection);
			data->redir->redirection = NULL;
		}
		free(data->redir);
		data->redir = NULL;
	}
}

void	start_heredoc_case(int j, char **argv, t_cmd **cmd_list, t_data *data)
{
	int	i;

	if (!(*cmd_list)->files || !(*cmd_list)->redirection)
		return ;
	i = -1;
	while ((*cmd_list)->files[++i])
	{
		if ((*cmd_list)->redirection[i] == HEREDOC)
		{
			(*cmd_list)->heredoc_delimiter = safe_strdup(
					(*cmd_list)->files[i], data);
			handle_heredoc(&j, argv, *cmd_list, data);
		}
	}
}

static void	exit_error_redir(char **argv, t_redir *redir, t_data *data)
{
	if (redir)
	{
		if (redir->redirection)
		{
			free(redir->redirection);
			redir->redirection = NULL;
		}
		if (redir->files)
		{
			free(redir->files);
			redir->files = NULL;
		}
		free(redir);
		redir = NULL;
	}
	exit_error_strs(argv, "malloc()", data);
}

static t_redir	*malloc_redir(char **argv, t_data *data)
{
	int		count;
	int		i;
	t_redir	*redir;

	count = 0;
	i = data->i;
	while (argv && argv[i] && is_redirection(argv[i]))
	{
		count++;
		i += 2;
	}
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		exit_error_redir(argv, redir, data);
	redir->redirection = (int *)ft_calloc(1, sizeof(int) * count);
	if (!redir->redirection)
		exit_error_redir(argv, redir, data);
	redir->files = (char **)ft_calloc(1, sizeof(char *) * (count + 1));
	if (!redir->files)
		exit_error_redir(argv, redir, data);
	redir->count = count;
	return (redir);
}

t_redir	*parse_start_redirection(char **argv, t_data *data)
{
	int		j;
	t_redir	*redir;

	redir = malloc_redir(argv, data);
	j = 0;
	while (argv[data->i] && is_redirection(argv[data->i]))
	{
		redir->redirection[j] = get_redirection(argv[data->i++]);
		if (argv[data->i])
			redir->files[j++] = safe_strdup(argv[data->i++], data);
	}
	redir->files[j] = NULL;
	return (redir);
}
