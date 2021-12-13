/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:39:37 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 20:04:08 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_of_args(int i, char **existing_args, char **strs)
{
	int	existing;
	int	new;

	existing = 0;
	while (existing_args && existing_args[existing])
		existing++;
	new = 0;
	while (strs[i])
	{
		new++;
		i++;
	}
	if (!new)
		return (0);
	return (existing + new);
}

void	refill_args(int i, char **strs, t_cmd **cmd_list, t_data *data)
{
	int		j;
	int		k;
	char	**existing_args;

	existing_args = copy_strs((*cmd_list)->args, data);
	j = get_nb_of_args(i, existing_args, strs);
	if (!j)
		return (free_double_str(existing_args));
	free_double_str((*cmd_list)->args);
	(*cmd_list)->args = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->args)
	{
		free_double_str(strs);
		exit_error_strs(existing_args, "malloc()", data);
	}
	j = 0;
	while (strs[i])
		(*cmd_list)->args[j++] = safe_strdup(strs[i++], data);
	k = 0;
	while (existing_args && existing_args[k])
		(*cmd_list)->args[j++] = safe_strdup(existing_args[k++], data);
	(*cmd_list)->args[j] = NULL;
	free_double_str(existing_args);
}

static int	get_nb_of_options(char **existing_options, char **strs)
{
	int	i;
	int	existing;
	int	new;

	existing = 0;
	while (existing_options && existing_options[existing])
		existing++;
	i = 1;
	new = 0;
	while (strs[i] && strs[i][0] == '-')
	{
		new++;
		i++;
	}
	if (!new)
		return (0);
	return (existing + new);
}

void	refill_options(int *i, char **strs, t_cmd **cmd_list, t_data *data)
{
	int		j;
	int		k;
	char	**existing_options;

	existing_options = copy_strs_and_free((*cmd_list)->options, data, strs);
	j = get_nb_of_options(existing_options, strs);
	if (!j)
		return (free_double_str(existing_options));
	(*cmd_list)->options = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->options)
	{
		free_double_str(strs);
		exit_error_strs(existing_options, "malloc()", data);
	}
	j = 0;
	while (strs[*i] && strs[*i][0] == '-')
		(*cmd_list)->options[j++] = safe_strdup(strs[(*i)++], data);
	k = 0;
	while (existing_options && existing_options[k])
		(*cmd_list)->options[j++] = safe_strdup(existing_options[k++], data);
	(*cmd_list)->options[j] = NULL;
	free_double_str(existing_options);
}
