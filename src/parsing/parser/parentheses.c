/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:13 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/05 14:38:28 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_parenthese(char *str)
{
	return (str_is_equal(str, "(")
		|| str_is_equal(str, ")"));
}

void	note_parenthese(int parenthese, t_cmd *cmd_list)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->parenthese = parenthese;
}

void	fill_parentheses(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		{
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
			note_parenthese(IN, cmd_list);
		}
		else if (argv[data->i])
		{
			handle_bin_cmd(delimiter, argv, cmd_list, data);
			note_parenthese(IN, cmd_list);
		}
		if (argv[data->i] && str_is_equal(argv[data->i], ")"))
			break ;
	}
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
	note_parenthese(FIRST, cmd_list);
	if (argv[data->i] && str_is_equal(argv[data->i], ")"))
	{
		data->i++;
		return ;
	}
	fill_parentheses(delimiter, argv, cmd_list, data);
	note_parenthese(IN, cmd_list);
	data->i++;
}
