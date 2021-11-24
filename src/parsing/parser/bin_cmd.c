/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:52:38 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/24 16:48:58 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_bin_cmd(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	create_new_cmd(&cmd_list, data);
	cmd_list->path = find_cmd_path(argv[data->i], NULL, data->all_paths, data);
	cmd_list->command = safe_strdup(argv[data->i], data);
	cmd_list->options = find_cmd_options(argv, data);
	cmd_list->args = find_cmd_args(argv, data);
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
}
