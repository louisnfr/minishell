/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:43:28 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 16:34:53 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exit_error_option_echo(char **strs, t_data *data)
{
	free_double_str(data->tmp_args);
	exit_error_strs(strs, "malloc()", data);
}

void	handle_option_echo(int j, t_cmd **cmd_list, t_data *data)
{
	char	**strs;
	int		i;
	t_bool	option;

	option = FALSE;
	data->to_suppress = safe_strdup(data->tmp_args[j], data);
	strs = safe_split(data->tmp_args[j], 32, data);
	i = 0;
	while (!j && strs && strs[i] && is_option_echo(strs[i]))
	{
		option = TRUE;
		i++;
	}
	if (option && !(*cmd_list)->options)
	{
		(*cmd_list)->options = (char **)ft_calloc(1, sizeof(char *) * 2);
		if (!(*cmd_list)->options)
			exit_error_option_echo(strs, data);
		(*cmd_list)->options[0] = safe_strdup("-n", data);
		(*cmd_list)->options[1] = NULL;
	}
	refill_args_after_check(i, strs, cmd_list, data);
	free_double_str(strs);
	clean_free(&data->to_suppress);
}
