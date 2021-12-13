/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:35:51 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 18:04:37 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_check_redir(char *arg)
{
	return (str_is_equal(arg, "<") || str_is_equal(arg, ">")
		|| str_is_equal(arg, "<<") || str_is_equal(arg, ">>"));
}

t_bool	check_redir_parenthese(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i] && argv[i + 1])
	{
		if (is_check_redir(argv[i]) && str_is_equal(argv[i + 1], ")"))
		{
			display_error_msg_delimiter(1, ')');
			free_double_str(argv);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	get_length_new_argv(char **argv)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (argv[i])
	{
		if (argv[i] && argv[i + 1] && argv[i + 2] && str_is_equal(argv[i], "2")
			&& str_is_equal(argv[i + 1], ">&")
			&& str_is_equal(argv[i + 2], "1"))
			i += 2;
		else if (argv[i] && argv[i + 1] && str_is_equal(argv[i], "2")
			&& str_is_equal(argv[i + 1], ">"))
			i++;
		else if (argv[i] && argv[i + 1] && str_is_equal(argv[i], "2")
			&& str_is_equal(argv[i + 1], ">>"))
			i++;
		i++;
		length++;
	}
	if (length == i)
		return (-1);
	return (length);
}

static char	*fill_str(int *i, char **argv, t_data *data)
{
	char	*str;

	if (argv[*i] && argv[*i + 1] && argv[*i + 2] && str_is_equal(argv[*i], "2")
		&& str_is_equal(argv[*i + 1], ">&")
		&& str_is_equal(argv[*i + 2], "1"))
	{
		str = safe_strjoin(argv[*i], argv[*i + 1], data);
		str = safe_strjoin_and_free(str, argv[*i + 2], data);
		(*i) += 2;
	}
	else if (argv[*i] && argv[*i + 1] && str_is_equal(argv[*i], "2")
		&& str_is_equal(argv[*i + 1], ">"))
	{
		str = safe_strjoin(argv[*i], argv[*i + 1], data);
		(*i)++;
	}
	else if (argv[*i] && argv[*i + 1] && str_is_equal(argv[*i], "2")
		&& str_is_equal(argv[*i + 1], ">>"))
	{
		str = safe_strjoin(argv[*i], argv[*i + 1], data);
		(*i)++;
	}
	else
		str = safe_strdup(argv[*i], data);
	return (str);
}

t_bool	fill_new_argv(int length, char **argv, char **new_argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < length && argv[i])
	{
		new_argv[j] = fill_str(&i, argv, data);
		if (!new_argv[j])
			return (FAIL);
		i++;
	}
	new_argv[j] = NULL;
	return (SUCCESS);
}
