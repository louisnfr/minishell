/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:32 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/22 11:52:38 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_unclosed_parentheses(char *input)
{
	int	i;
	int	input_length;

	i = -1;
	input_length = ft_strlen(input);
	while (input && ++i < input_length && input[i] && input[i] != '#')
	{
		if (input[i] && input[i] == ')')
		{
			ft_putstr_fd("bash: syntax error: unclosed parentheses `)'\n", 2);
			return (FAIL);
		}
		if (input[i] && input[i] == '(')
		{
			i++;
			while (input[i] && input[i] != ')')
				i++;
			if (input[i])
				continue ;
			ft_putstr_fd("bash: syntax error: unclosed parentheses `('\n", 2);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

static t_bool	char_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

t_bool	check_unclosed_quotes(char *input)
{
	int		i;
	char	quote;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] && char_is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				continue ;
			ft_putstr_fd("bash: syntax error: unclosed quotes `", 2);
			ft_putchar_fd(quote, 2);
			ft_putstr_fd("'\n", 2);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

static int	get_length(char *input, int length)
{
	int	input_len;

	if (!input)
		return (0);
	input_len = ft_strlen(input);
	while (length < input_len && input[length++])
	{
		while (length < input_len && input[length] && ft_isspace(input[length]))
			length++;
		if (input[length] && input[length] == '#')
			break ;
		while (length < input_len && input[length] && !ft_isspace(input[length]))
		{
			if (input[length] && input[length] == '\"')
			{
				length++;
				while (length < input_len && input[length] && input[length] != '\"')
					length++;
			}
			else if (input[length] && input[length] == '\'')
			{
				length++;
				while (length < input_len && input[length] && input[length] != '\'')
					length++;
			}		
			length++;
		}
	}
	return (length);
}

char	*check_comment(char *input)
{
	int		i;
	int		length;
	char	*new_input;

	if (!input)
		return (NULL);
	new_input = NULL;
	length = 0;
	length = get_length(input, length);
	if (length == (int)ft_strlen(input))
		return (input);
	new_input = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_input)
		return (NULL);
	i = -1;
	while (++i < length)
		new_input[i] = input[i];
	new_input[i] = '\0';
	clean_free(&input);
	return (new_input);
}

char	*check_input(char *input)
{
	char	*new_str;

	if (!input)
		return (NULL);
	new_str = NULL;
	new_str = check_comment(input);
	if (!check_unclosed_quotes(new_str) || !check_unclosed_parentheses(new_str))
	{
		clean_free(&new_str);
		return (NULL);
	}
	return (new_str);
}
