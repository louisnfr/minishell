/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:53:13 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 13:53:21 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_length(char *command)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] && (command[i] == '\'' || command[i] == '\"'))
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
			{
				j++;
				i++;
			}
			i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j + 1);
}

static char	*remove_quote_command(char *command, t_data *data)
{
	int		i;
	int		j;
	char	quote;
	char	*new_command;

	new_command = (char *)ft_calloc(1, sizeof(char) * get_length(command));
	if (!new_command)
		exit_error_str(NULL, "malloc()", data);
	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] && (command[i] == '\'' || command[i] == '\"'))
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
				new_command[j++] = command[i++];
			i++;
		}
		else
			new_command[j++] = command[i++];
	}
	new_command[j] = '\0';
	clean_free(&command);
	return (new_command);
}

static t_bool	check_dollar_simple_quote(char *command)
{
	int		i;
	int		command_length;

	command_length = ft_strlen(command);
	i = -1;
	while (++i < command_length && command[i])
	{
		if (command[i] && command[i] == '\'')
		{
			i++;
			while (command[i] && command[i] != '\'')
				i++;
			i++;
		}
		if (command[i] && command[i] == '$')
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	check_dollar_double_quote(char *command)
{
	int		i;
	int		command_length;

	command_length = ft_strlen(command);
	i = -1;
	while (++i < command_length && command[i])
	{
		if (command[i] && command[i] == '\"')
		{
			i++;
			while (command[i] && command[i] != '\"')
			{
				if (command[i] && command[i] == '$')
					return (TRUE);
				i++;
			}
		}
	}
	return (FALSE);
}

int	need_recheck(t_cmd **cmd_list, t_data *data)
{
	if (!(*cmd_list)->command || str_is_equal((*cmd_list)->command, "\"\"")
		|| str_is_equal((*cmd_list)->command, "\'\'"))
		return (0);
	if (!ft_strchr((*cmd_list)->command, '$')
		&& (ft_strchr((*cmd_list)->command, '\"')
			|| ft_strchr((*cmd_list)->command, '\'')))
	{
		(*cmd_list)->command = remove_quote_command((*cmd_list)->command, data);
		(*cmd_list)->path = find_cmd_path(
				(*cmd_list)->command, NULL, data->all_paths, data);
		return (0);
	}
	if (check_dollar_simple_quote((*cmd_list)->command))
		return (0);
	if (check_dollar_double_quote((*cmd_list)->command))
		return (2);
	return (1);
}
