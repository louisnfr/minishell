/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:32 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/07 17:39:32 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_unclosed_quotes(char *input, char quote)
{
	int	i;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] == quote)
		{
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				continue ;
			printf("bash: syntax error: unclosed quotes `%c'\n", quote);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

static int	get_length(char *input, int length)
{
	while (input && input[++length])
	{
		while (input[length] && ft_isspace(input[length]))
			length++;
		if (input[length] == '#')
			break ;
		while (input[length] && !ft_isspace(input[length]))
		{
			if (input[length] == '\"')
			{
				length++;
				while (input[length] && input[length] != '\"')
					length++;
			}
			else if (input[length] == '\'')
			{
				length++;
				while (input[length] && input[length] != '\'')
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
	length = -1;
	length = get_length(input, length);
	if (length == (int)ft_strlen(input))
		return (input);
	new_input = (char *)malloc(sizeof(char) * (length + 1));
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
	if (!check_unclosed_quotes(new_str, '\"')
		|| !check_unclosed_quotes(new_str, '\''))
		return (NULL);
	return (new_str);
}
