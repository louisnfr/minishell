/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:13 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:48:14 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_parenthese(int parenthese, t_cmd *cmd_list)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->parenthese = parenthese;
}

void	handle_parentheses(int delimiter, char **argv, t_data *data)
{
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	data->i++;
	if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(delimiter, argv, cmd_list, data);
	else if (argv[data->i])
		handle_bin_cmd(delimiter, argv, cmd_list, data);
	fill_parenthese(FIRST, cmd_list);
	if (argv[data->i] && str_is_equal(argv[data->i], ")"))
	{
		data->i++;
		return ;
	}
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		{
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
			fill_parenthese(IN, cmd_list);
		}
		else if (argv[data->i])
		{
			handle_bin_cmd(delimiter, argv, cmd_list, data);
			fill_parenthese(IN, cmd_list);
		}
		if (argv[data->i] && str_is_equal(argv[data->i], ")"))
			break ;
	}
	fill_parenthese(IN, cmd_list);
	data->i++;
}
