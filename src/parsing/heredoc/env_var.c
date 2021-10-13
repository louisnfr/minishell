/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:08:45 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/13 14:08:47 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_double_dollars(int *i, int *length, char *str)
{
	if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '$')
	{
		(*i) += 2;
		if (str[*i])
			(*length) += 2;
		else
			(*length)++;
		return (1);
	}
	return (0);
}

static int	heredoc_length_new_input(char *str, t_data *data)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	if (!str || !str[i])
		return (0);
	while (str && str[i] && str[i + 1])
	{
		if (heredoc_double_dollars(&i, &length, str))
			continue ;
		if (str[i] && str[i + 1] && str[i] == '$'
			&& !is_charset_env(str[i + 1]))
			handle_env_variable(&i, &length, str, data);
		else
		{
			i++;
			length++;
		}
	}
	return (++length);
}

static int	heredoc_handle_special_case(char *new_str, char *str, int *i, int *j)
{
	int	count;

	count = 0;
	if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '$')
	{
		while (str[*i] && count++ < 2)
			new_str[(*j)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

static int	heredoc_fill_new_input(char *new_str, char *str, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !str[i])
		return (0);
	while (str && str[i] && str[i + 1])
	{
		if (heredoc_handle_special_case(new_str, str, &i, &j))
			continue ;
		if (str[i] && str[i + 1] && str[i] == '$'
			&& !is_charset_env(str[i + 1]))
			fill_env_value(new_str, &j, get_env_value(str, &i, data));
		else
			new_str[j++] = str[i++];
	}
	new_str[j++] = str[i];
	new_str[j] = '\0';
	return (1);
}

char	*heredoc_env_variable(char *input, t_data *data)
{
	char	*new_input;
	int		new_length;

	new_input = NULL;
	new_length = heredoc_length_new_input(input, data);
	new_input = (char *)malloc(sizeof(char) * (new_length + 1));
	if (!new_input)
		return (NULL);
	heredoc_fill_new_input(new_input, input, data);
	clean_free(&input);
	return (new_input);
}
