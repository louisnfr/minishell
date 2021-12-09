/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:18 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/09 20:10:30 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reparse_options_in_args(int *j, t_cmd **cmd_list, t_data *data)
{
	int		i;
	char	**strs;

	data->to_suppress = safe_strdup((*cmd_list)->args[*j], data);
	strs = safe_split((*cmd_list)->args[*j], 32, data);
	i = 0;
	refill_options_after_check(&i, strs, cmd_list, data);
	refill_args_after_check(i, strs, cmd_list, data);
	free_double_str(strs);
	clean_free(&data->to_suppress);
}

static void	handle_quotes(int *i, char *arg)
{
	char	quote;

	if (arg[*i] == '\'' || arg[*i] == '\"')
	{
		quote = arg[(*i)++];
		while (arg[*i] && arg[*i] != quote)
			(*i)++;
	}
}

static t_bool	is_option_echo(char *arg)
{
	int		i;
	int		ret;

	ret = FAIL;
	i = 0;
	while (++i < (int)ft_strlen(arg))
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			handle_quotes(&i, arg);
		else if (arg[i] && arg[i] == 'n')
		{
			i++;
			while (arg[i] && arg[i] == 'n')
				i++;
			if (arg[i])
				break ;
			ret = SUCCESS;
		}
		else
			break ;
	}
	return (ret);
}

static void	handle_option_echo(int j, t_cmd **cmd_list, t_data *data)
{
	char	**strs;
	int		i;
	t_bool	option;

	option = FALSE;
	data->to_suppress = safe_strdup((*cmd_list)->args[j], data);
	strs = safe_split((*cmd_list)->args[j], 32, data);
	i = 0;
	while (strs && strs[i] && is_option_echo(strs[i]))
	{
		option = TRUE;
		i++;
	}
	if (option && !(*cmd_list)->options)
	{
		(*cmd_list)->options = (char **)ft_calloc(1, sizeof(char *) * 2);
		if (!(*cmd_list)->options)
			exit_error_bool("malloc()", data);
		(*cmd_list)->options[0] = safe_strdup("-n", data);
		(*cmd_list)->options[1] = NULL;
	}
	refill_args_after_check(i, strs, cmd_list, data);
	free_double_str(strs);
	clean_free(&data->to_suppress);
}

void	check_options_in_args(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	**tmp_args;

	if (!cmd_list->args)
		return ;
	tmp_args = copy_strs(cmd_list->args, data);
	i = -1;
	while (tmp_args && tmp_args[++i])
	{
		if (str_is_equal(cmd_list->command, "echo")
			&& str_is_in_str(tmp_args[i], "-n"))
			handle_option_echo(i, &cmd_list, data);
		else if (!cmd_list->is_builtin && ft_strchr(tmp_args[i], '-'))
			reparse_options_in_args(&i, &cmd_list, data);
	}
	free_double_str(tmp_args);
}
