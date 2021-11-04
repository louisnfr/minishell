/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:52 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 16:35:53 by efrancon         ###   ########.fr       */
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
