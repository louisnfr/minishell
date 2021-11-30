/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:39:37 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/30 11:39:39 by efrancon         ###   ########.fr       */
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

	existing_args = copy_strs_and_free((*cmd_list)->args, data);
	j = get_nb_of_args(i, existing_args, strs);
	if (!j)
		return (free_double_str(existing_args));
	(*cmd_list)->args = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->args)
	{
		exit_error_bool("malloc()", data);
		return (free_double_str(existing_args));
	}
	j = 0;
	while (strs[i] && strs[i][0] == '-')
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

	existing_options = copy_strs_and_free((*cmd_list)->options, data);
	j = get_nb_of_options(existing_options, strs);
	if (!j)
		return (free_double_str(existing_options));
	(*cmd_list)->options = (char **)ft_calloc(1, sizeof(char *) * (j + 1));
	if (!(*cmd_list)->options)
	{
		exit_error_bool("malloc()", data);
		return (free_double_str(existing_options));
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

void	reparse_command(t_cmd **cmd_list, t_data *data)
{
	char	**strs;
	int		i;

	strs = safe_split((*cmd_list)->command, 32, data);
	clean_free(&(*cmd_list)->command);
	(*cmd_list)->command = safe_strdup(strs[0], data);
	i = 1;
	refill_options(&i, strs, cmd_list, data);
	refill_args(i, strs, cmd_list, data);
	free_double_str(strs);
}
