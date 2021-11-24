/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:46:12 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/24 14:37:44 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_redir(t_redir *redir)
{
	if (redir)
	{
		free_double_str(redir->files);
		if (redir->redirection)
		{
			free(redir->redirection);
			redir->redirection = NULL;
		}
		free(redir);
	}
	redir = NULL;
}

t_redir	*malloc_redir(char **argv, t_data *data)
{
	int		count;
	int		i;
	t_redir	*redir;

	count = 0;
	i = data->i;
	while (argv[i] && is_redirection(argv[i]))
	{
		count++;
		i += 2;
	}
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		exit_error_bool("malloc()", data);
	redir->redirection = (int *)ft_calloc(1, sizeof(int) * count);
	if (!redir->redirection)
		exit_error_bool("malloc()", data);
	redir->files = (char **)ft_calloc(1, sizeof(char *) * (count + 1));
	if (!redir->files)
		exit_error_bool("malloc()", data);
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
