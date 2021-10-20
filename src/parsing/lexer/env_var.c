/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:39:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/20 13:24:48 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_cases(int *double_quotes, char *new_str, char *str, int *i, int *j)
{
	int	count;

	count = 0;
	if (*double_quotes != -1 && str[*i] && str[*i] == '\'')
	{
		new_str[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != '\'')
			new_str[(*j)++] = str[(*i)++];
	}
	if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '$')
	{
		while (str[*i] && count++ < 2)
			new_str[(*j)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

void	fill_env_value(char *new_str, int *j, char *value)
{
	int	k;

	if (!value)
		return ;
	k = 0;
	while (value && value[k])
		new_str[(*j)++] = value[k++];
}

static int	fill_new_input(char *new_str, char *str, t_data *data)
{
	int	i;
	int	j;
	int	double_quotes;
	int	str_length;

	i = 0;
	j = 0;
	double_quotes = 1;
	str_length = ft_strlen(str);
	if (!str || !str[i])
		return (0);
	while (str[i] && str[i + 1] && i < str_length)
	{
		if (str[i] && str[i] == '\"')
			double_quotes *= -1;
		if (handle_special_cases(&double_quotes, new_str, str, &i, &j))
			continue ;
		if (str[i] && str[i + 1] && str[i] == '$'
			&& !is_charset_env(str[i + 1]))
			fill_env_value(new_str, &j, get_env_value(str, &i, data));
		else
			new_str[j++] = str[i++];
	}
	if (str[i] && i < str_length)
		new_str[j++] = str[i];
	new_str[j] = '\0';
	return (1);
}

char	*parse_env_variable(char *input, t_data *data)
{
	char	*new_input;
	int		new_length;

	new_input = NULL;
	new_length = get_length_new_input(input, data);
	new_input = (char *)ft_calloc(1, sizeof(char) * (new_length + 1));
	if (!new_input)
		return (NULL);
	fill_new_input(new_input, input, data);
	clean_free(&input);
	return (new_input);
}
