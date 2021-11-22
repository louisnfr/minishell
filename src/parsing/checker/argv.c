/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:39:48 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/15 16:09:44 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_length(char **argv)
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

char	**handle_error_redirections(char **argv, t_data *data)
{
	char	**new_argv;
	int		length;

	length = get_length(argv);
	if (length == -1)
		return (argv);
	new_argv = NULL;
	new_argv = (char **)ft_calloc(1, sizeof(char *) * (length + 1));
	if (!new_argv)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	if (!fill_new_argv(length, argv, new_argv, data))
		return (NULL);
	free_double_str(&(*argv));
	return (new_argv);
}

char	**check_argv(char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (!argv[i])
		return (NULL);
	if (argv[i] && str_is_equal(argv[i], ".") && !argv[i + 1])
		return (display_error_msg_simple_dot(argv));
	if (argv[i] && (is_delimiter(argv[i]) || str_is_equal(argv[i], "&")))
		return (syntax_error_str_msg(argv[i], argv));
	if (argv[i] && (is_redirection(argv[i]) || str_is_equal(argv[i], "<<<"))
		&& !str_is_equal(argv[i], "<") && !str_is_equal(argv[i], ">"))
		return (syntax_error_str_msg("newline", argv));
	while (argv[i + 1])
		i++;
	if (argv[i] && (is_delimiter(argv[i]) || str_is_equal(argv[i], "&")))
		return (syntax_error_str_msg(argv[i], argv));
	if (argv[i] && (is_redirection(argv[i]) || str_is_equal(argv[i], "<<<")))
		return (syntax_error_str_msg("newline", argv));
	argv = handle_error_redirections(&(*argv), data);
	return (argv);
}
