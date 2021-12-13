/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:39:48 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:12:33 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	str_is_in_str(char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s1[++i])
	{
		if (s1[i] == s2[j])
		{
			while (s1[i] && s2[j] && s1[i++] == s2[j])
				j++;
			break ;
		}
	}
	if (s2[j])
		return (FAIL);
	return (SUCCESS);
}

static char	**handle_error_redirections(char *input, char **argv, t_data *data)
{
	char	**new_argv;
	int		length;

	if (!str_is_in_str(input, "2>") && !str_is_in_str(input, "2>>")
		&& !str_is_in_str(input, "2>&1"))
		return (argv);
	length = get_length_new_argv(argv);
	if (length == -1)
		return (argv);
	new_argv = NULL;
	new_argv = (char **)ft_calloc(1, sizeof(char *) * (length + 1));
	if (!new_argv)
		exit_error_redirections(input, argv, data);
	if (!fill_new_argv(length, argv, new_argv, data))
	{
		free_double_str(&(*argv));
		return (NULL);
	}
	free_double_str(&(*argv));
	if (new_argv && new_argv[0] && str_is_equal(new_argv[0], "2>&1")
		&& !new_argv[1])
		return (syntax_error_str_msg(">", new_argv));
	return (new_argv);
}

static t_bool	check_error_parentheses(int *i, char **argv)
{
	while (argv[*i + 1])
	{
		if ((str_is_equal(argv[*i], ")")
				&& !is_delimiter(argv[*i + 1])
				&& !is_redirection(argv[*i + 1])
				&& !is_parenthese(argv[*i + 1]))
			|| (str_is_equal(argv[*i + 1], "(")
				&& !is_delimiter(argv[*i])
				&& !is_redirection(argv[*i])
				&& !is_parenthese(argv[*i])))
		{
			display_error_msg_delimiter(1, ')');
			free_double_str(argv);
			return (FAIL);
		}
		(*i)++;
	}
	return (SUCCESS);
}

t_bool	check_empty_parentheses(char **argv)
{
	int	i;

	i = 0;
	while (argv[i + 1])
	{
		if (str_is_equal(argv[i], "(") && str_is_equal(argv[i + 1], ")"))
		{
			display_error_msg_delimiter(1, ')');
			free_double_str(argv);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

char	**check_argv(char *input, char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (!argv[i])
		return (NULL);
	if (!check_empty_parentheses(argv))
		return (NULL);
	if (argv[i] && str_is_equal(argv[i], ".") && !argv[i + 1])
		return (display_error_msg_simple_dot(argv));
	if (argv[i] && (is_delimiter(argv[i]) || str_is_equal(argv[i], "&")))
		return (syntax_error_str_msg(argv[i], argv));
	if (argv[i] && (str_is_equal(argv[i], "<<<") || str_is_equal(argv[i], "2>")
			|| str_is_equal(argv[i], "2>>")))
		return (syntax_error_str_msg("newline", argv));
	if (!check_error_parentheses(&i, argv))
		return (NULL);
	if (argv[i] && (is_delimiter(argv[i]) || str_is_equal(argv[i], "&")))
		return (syntax_error_str_msg(argv[i], argv));
	if (argv[i] && (is_redirection(argv[i]) || str_is_equal(argv[i], "<<<")))
		return (syntax_error_str_msg("newline", argv));
	argv = handle_error_redirections(input, &(*argv), data);
	if (argv && !check_redir_parenthese(argv))
		return (NULL);
	return (argv);
}
