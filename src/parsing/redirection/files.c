/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:30:38 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:08:58 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_existing_files(t_cmd *cmd_list)
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

static int	fill_files(
	int nb_existing_files, t_cmd *cmd_list, t_data *data)
{
	int	i;

	i = -1;
	while (data->redir->files[++i])
	{
		cmd_list->redirection[i] = data->redir->redirection[i];
		cmd_list->files[i] = safe_strdup(data->redir->files[i], data);
	}
	return (data->redir->count + nb_existing_files);
}

int	malloc_files(char **argv, int length, t_cmd *cmd_list, t_data *data)
{
	int	nb_existing_files;

	if (!length && !data->redir)
		return (0);
	nb_existing_files = 0;
	if (data->redir && data->redir->count)
		length += data->redir->count;
	if (cmd_list->files)
	{
		nb_existing_files = count_existing_files(cmd_list);
		length += nb_existing_files;
	}
	cmd_list->redirection = (int *)ft_calloc(1, sizeof(int) * length);
	if (!cmd_list->redirection)
		exit_error_strs(argv, "malloc()", data);
	cmd_list->files = (char **)ft_calloc(1, sizeof(char *) * (length + 1));
	if (!cmd_list->files)
		exit_error_strs(argv, "malloc()", data);
	if (data->redir)
		return (fill_files(nb_existing_files, cmd_list, data));
	return (nb_existing_files);
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

char	**copy_existing_files(
	char **argv, int **copy_redir, t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		count;
	char	**copy_files;

	if (!cmd_list->files)
		return (NULL);
	count = 0;
	while (cmd_list->files[count])
		count++;
	copy_files = (char **)ft_calloc(1, sizeof(char *) * (count + 1));
	if (!copy_files)
		exit_error_strs(argv, "malloc()", data);
	*copy_redir = (int *)ft_calloc(1, sizeof(int) * count);
	if (!*copy_redir)
		exit_error_files(copy_files, argv, data);
	i = -1;
	while (cmd_list->files[++i])
		copy_files[i] = safe_strdup(cmd_list->files[i], data);
	copy_files[i] = NULL;
	i = -1;
	while (++i < count)
		(*copy_redir)[i] = cmd_list->redirection[i];
	return (copy_files);
}
