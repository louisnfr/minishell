/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 16:46:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_copy_args(
	char **strs, char **strs_2, t_cmd *cmd_list, t_data *data)
{
	if (cmd_list->path)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit_error_child(strs, strs_2, "malloc()", data);
	}
	free_double_str(strs_2);
	exit_error_strs(strs, "malloc()", data);
}

char	**copy_args(char **strs, char **strs_2, t_cmd *cmd_list, t_data *data)
{
	int		i;
	int		j;
	char	**strs_copy;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		i++;
	if (i < 2)
		return (NULL);
	strs_copy = (char **)ft_calloc(1, sizeof(char *) * i);
	if (!strs_copy)
		exit_error_copy_args(strs, strs_2, cmd_list, data);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		if (!str_is_equal(strs[i], data->to_suppress))
			strs_copy[j++] = safe_strdup(strs[i], data);
	}
	strs_copy[j] = NULL;
	return (strs_copy);
}

static void	free_cmd_args(t_cmd **cmd_list)
{
	int	i;

	i = -1;
	if ((*cmd_list)->args)
	{
		while ((*cmd_list)->args[++i])
			clean_free(&(*cmd_list)->args[i]);
		free((*cmd_list)->args);
		(*cmd_list)->args = NULL;
	}
}

static void	reparse_options_in_args(int j, t_cmd **cmd_list, t_data *data)
{
	int		i;
	char	**strs;

	data->to_suppress = safe_strdup(data->tmp_args[j], data);
	strs = safe_split(data->tmp_args[j], 32, data);
	i = 0;
	refill_options_after_check(&i, strs, cmd_list, data);
	refill_args_after_check(i, strs, cmd_list, data);
	free_double_str(strs);
	clean_free(&data->to_suppress);
}

void	check_options_in_args(t_cmd *cmd_list, t_data *data)
{
	int		i;

	if (!cmd_list->args)
		return ;
	data->tmp_args = copy_strs(cmd_list->args, data);
	free_cmd_args(&cmd_list);
	i = -1;
	while (data->tmp_args && data->tmp_args[++i])
	{
		if (!i && str_is_equal(cmd_list->command, "echo")
			&& str_is_in_str(data->tmp_args[i], "-n"))
			handle_option_echo(i, &cmd_list, data);
		else if (!cmd_list->is_builtin && ft_strchr(data->tmp_args[i], '-'))
			reparse_options_in_args(i, &cmd_list, data);
	}
	if (!cmd_list->args)
		cmd_list->args = copy_strs(data->tmp_args, data);
	free_double_str(data->tmp_args);
}
