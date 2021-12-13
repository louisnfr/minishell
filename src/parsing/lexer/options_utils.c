/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:50:20 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:25:19 by efrancon         ###   ########.fr       */
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
	return (existing + new);
}

void	refill_args_after_check(
	int i, char **strs, t_cmd **cmd_list, t_data *data)
{
	int		j;
	int		k;
	char	**existing_args;

	existing_args = copy_args(data->tmp_args, strs, *cmd_list, data);
	j = get_nb_of_args(i, existing_args, strs);
	if (!j)
		return (free_double_str(existing_args));
	(*cmd_list)->args = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->args)
		exit_error_refill(strs, existing_args, *cmd_list, data);
	j = 0;
	while (strs[i])
		(*cmd_list)->args[j++] = safe_strdup(strs[i++], data);
	k = 0;
	while (existing_args && existing_args[k])
		(*cmd_list)->args[j++] = safe_strdup(existing_args[k++], data);
	(*cmd_list)->args[j] = NULL;
	free_double_str(existing_args);
}

static char	**copy_options_and_free(
	char **strs, char **strs_2, t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	**strs_copy;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		i++;
	if (i < 1)
	{
		free_double_str(strs);
		return (NULL);
	}
	strs_copy = (char **)ft_calloc(1, sizeof(char *) * (i + 1));
	if (!strs_copy)
		exit_error_refill(strs_2, NULL, cmd_list, data);
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	free_double_str(strs);
	return (strs_copy);
}

static int	get_nb_of_options(char **existing_options, char **strs)
{
	int	i;
	int	existing;
	int	new;

	existing = 0;
	while (existing_options && existing_options[existing])
		existing++;
	i = 0;
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

void	refill_options_after_check(
	int *i, char **strs, t_cmd **cmd_list, t_data *data)
{
	int		j;
	int		k;
	char	**existing_options;

	existing_options = copy_options_and_free(
			(*cmd_list)->options, strs, *cmd_list, data);
	j = get_nb_of_options(existing_options, strs);
	if (!j)
		return (free_double_str(existing_options));
	(*cmd_list)->options = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->options)
		exit_error_refill(existing_options, strs, *cmd_list, data);
	j = 0;
	while (strs[*i] && strs[*i][0] == '-')
		(*cmd_list)->options[j++] = safe_strdup(strs[(*i)++], data);
	k = 0;
	while (existing_options && existing_options[k])
		(*cmd_list)->options[j++] = safe_strdup(existing_options[k++], data);
	(*cmd_list)->options[j] = NULL;
	free_double_str(existing_options);
}
