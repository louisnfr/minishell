/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/24 23:17:21 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_existing_files(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list->files[i])
		i++;
	free_double_str(cmd_list->files);
	free(cmd_list->redirection);
	cmd_list->redirection = NULL;
	return (i);
}

int	malloc_files(int length, t_redir *redir, t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	nb_existing_files;

	if (!length && !redir)
		return (0);
	nb_existing_files = 0;
	if (redir)
		length += redir->count;
	if (cmd_list->files)
	{
		nb_existing_files = count_existing_files(cmd_list);
		length += nb_existing_files;
	}
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
	if (redir)
		return (redir->count + nb_existing_files);
	return (nb_existing_files);
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
	return (malloc_files(length, redir, cmd_list, data));
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

char	**copy_existing_files(int **copy_redir, t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		count;
	char	**copy_files;

	count = 0;
	while (cmd_list->files[count])
		count++;
	copy_files = (char **)ft_calloc(1, sizeof(char *) * (count + 1));
	if (!copy_files)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	*copy_redir = (int *)ft_calloc(1, sizeof(int) * count);
	if (!*copy_redir)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	i = -1;
	while (cmd_list->files[++i])
		copy_files[i] = safe_strdup(cmd_list->files[i], data);
	copy_files[i] = NULL;
	i = -1;
	while (++i < count)
		(*copy_redir)[i] = cmd_list->redirection[i];
	return (copy_files);
}

void	fill_existing_files_redir(
	int *redir, char **files, t_cmd *cmd_list, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (files[++i])
		cmd_list->files[i] = safe_strdup(files[i], data);
	j = -1;
	while (++j < i)
		cmd_list->redirection[j] = redir[j];
}

void	parse_redirections(
	t_redir *redir, char **argv, t_cmd **cmd_list, t_data *data)
{
	int		redirection;
	int		j;
	char	**existing_files;
	int		*existing_redir;

	redirection = 0;
	existing_files = NULL;
	existing_redir = NULL;
	parse_redirections_heredoc(argv, *cmd_list, data);
	while (*cmd_list && (*cmd_list)->next)
		(*cmd_list) = (*cmd_list)->next;
	if ((*cmd_list)->files)
		existing_files = copy_existing_files(&existing_redir, *cmd_list, data);
	j = get_length_redir(redir, argv, *cmd_list, data);
	if (existing_files && existing_redir)
		fill_existing_files_redir(existing_redir, existing_files, *cmd_list, data);
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
	(*cmd_list)->files[j] = NULL;
	if (existing_files)
		free_double_str(existing_files);
	if (existing_redir)
		free(existing_redir);
}
