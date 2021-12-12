/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:13 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 16:03:17 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_parenthese(char *str)
{
	return (str_is_equal(str, "(")
		|| str_is_equal(str, ")"));
}

static void	note_parenthese(int parenthese, t_cmd *cmd_list)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->parenthese = parenthese;
}

static void	fill_parentheses(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	if (argv[data->i] && is_delimiter(argv[data->i]))
		delimiter = get_delimiter(argv[data->i++]);
	clean_redir(data);
	if (argv[data->i] && is_redirection(argv[data->i]))
		data->redir = parse_start_redirection(argv, data);
	if (!argv[data->i] || str_is_equal(argv[data->i], ")")
		|| (argv[data->i] && is_delimiter(argv[data->i])))
	{
		create_new_cmd(&cmd_list, data);
		parse_redirections(argv, &cmd_list, data);
		return ;
	}
	parse_cmd(delimiter, argv, &cmd_list, data);
	parse_end_cmd(argv, &cmd_list, data);
}

void	handle_parentheses(int delimiter, char **argv, t_data *data)
{
	t_cmd	*cmd_list;
	t_bool	is_first;

	data->redir = NULL;
	is_first = TRUE;
	cmd_list = data->cmd_list;
	data->i++;
	data->par_lvl++;
	while (argv[data->i])
	{
		fill_parentheses(delimiter, argv, cmd_list, data);
		if (is_first)
		{
			note_parenthese(FIRST, cmd_list);
			is_first = FALSE;
		}
		else
			note_parenthese(IN, cmd_list);
		if (argv[data->i] && str_is_equal(argv[data->i], ")"))
			break ;
	}
	note_parenthese(LAST, cmd_list);
	if (argv[data->i])
		data->i++;
	data->par_lvl--;
}
