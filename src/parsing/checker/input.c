/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:40:02 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 16:41:57 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	length_quotes(int *length, int input_len, char *input)
{
	if (input[*length] && input[*length] == '\"')
	{
		(*length)++;
		while (*length < input_len && input[*length] && input[*length] != '\"')
			(*length)++;
	}
	else if (input[*length] && input[*length] == '\'')
	{
		(*length)++;
		while (*length < input_len && input[*length] && input[*length] != '\'')
			(*length)++;
	}
}

static int	get_length(char *input)
{
	int	input_len;
	int	length;

	length = 0;
	if (!input)
		return (0);
	input_len = ft_strlen(input);
	while (length < input_len && input[length])
	{
		while (length < input_len && input[length] && ft_isspace(input[length]))
			length++;
		if (input[length] && input[length] == '#')
			break ;
		while (length < input_len && input[length]
			&& !ft_isspace(input[length]))
		{
			length_quotes(&length, input_len, input);
			length++;
		}
	}
	return (length);
}

static char	*check_comment(char *input, t_data *data)
{
	int		i;
	int		length;
	char	*new_input;

	if (!input)
		return (NULL);
	new_input = NULL;
	length = get_length(input);
	if (length == ft_strlen(input))
		return (input);
	new_input = (char *)ft_calloc(1, sizeof(char) * (length + 1));
	if (!new_input)
		exit_error_str(input, "malloc()", data);
	i = -1;
	while (++i < length)
		new_input[i] = input[i];
	new_input[i] = '\0';
	clean_free(&input);
	return (new_input);
}

char	*check_input(char *input, t_data *data)
{
	char	*new_str;

	if (!input)
		return (NULL);
	new_str = NULL;
	new_str = check_comment(input, data);
	if (!check_unclosed_quotes(new_str) || !check_unclosed_parentheses(new_str))
	{
		clean_free(&new_str);
		return (NULL);
	}
	return (new_str);
}
