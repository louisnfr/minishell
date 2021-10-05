/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:26:59 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/05 14:27:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_is_charset(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == ';');
}

int	char_is_delimiter(char c)
{
	return (c == '&' || c == '|' || c == ';');
}

int	check_multiple_delimiters(char c1, char c2, char delimiter1, char delimiter2)
{
	if (c1 == delimiter1)
	{
		if (c2 == delimiter1)
			return (2);
		return (1);
	}
	if (c1 == delimiter2)
	{
		if (c2 == delimiter2)
			return (2);
		return (1);
	}
	return (0);
}

int	is_other_delimiter(char c1, char c2, char delimiter)
{
	if (delimiter == '|')
		return (check_multiple_delimiters(c1, c2, '&', ';'));
	if (delimiter == '&')
		return (check_multiple_delimiters(c1, c2, '|', ';'));
	if (delimiter == ';')
		return (check_multiple_delimiters(c1, c2, '|', '&'));
	return (0);
}

int	display_error_msg_delimiter(int count, char delimiter)
{
	if (count == 1)
		printf("bash: syntax error near unexpected token `%c'\n", delimiter);
	else
		printf("bash: syntax error near unexpected token `%c%c'\n", delimiter, delimiter);
	return (0);
}

int	check_error_delimiter(int j, char *str, int delimiter)
{
	int	ret ;

	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j && str[j] == delimiter)
	{
		if (str[j + 1] == delimiter)
			return(display_error_msg_delimiter(2, str[j]));
		return(display_error_msg_delimiter(1, str[j]));
	}
	ret = is_other_delimiter(str[j], str[j + 1], delimiter);
	if (ret == 1)
		return(display_error_msg_delimiter(1, str[j]));
	if (ret == 2)
		return(display_error_msg_delimiter(2, str[j]));
	return (1);
}

int	check_delimiter(char *str, char delimiter, int *i, int *words)
{
	int	count;
	int	j;

	count = 0;
	if (str[*i] != delimiter)
		return (1);
	(*words)++;
	while (str[*i] && str[*i] == delimiter)
	{
		(*i)++;
		count++;
	}
	if ((delimiter == '|' && count == 3) || (delimiter == '&' && count == 3))
		return(display_error_msg_delimiter(1, delimiter));
	if ((delimiter == '|' && count > 3) || (delimiter == '&' && count > 3) || (delimiter == ';' && count > 1))
		return(display_error_msg_delimiter(2, delimiter));
	j = *i;
	return (check_error_delimiter(j, str, delimiter));
}

int	count_arguments(char *str)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!char_is_charset(str[i]))
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
					i++;
				i++;
			}
			if (str[i] == '\"')
			{
				i++;
				while (str[i] && str[i] != '\"')
					i++;
				i++;
			}
			else
			{
				while (str[i] && !char_is_charset(str[i]))
					i++;
			}
			args++;
		}
		if (!check_delimiter(str, '|', &i, &args)
			|| !check_delimiter(str, '&', &i, &args)
			|| !check_delimiter(str, ';', &i, &args))
			return (-1);
		while (str[i] && ft_isspace(str[i]))
			i++;
	}
	return (args);
}

int	handle_words(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp[j] && !char_is_charset(tmp[j]))
		j++;
	free(tmp);
	tmp = NULL;
	strs[i] = (char *)malloc(sizeof(char) * (j + 1));
	if (!strs[i])
		return (0);
	j = 0;
	while (**str && !char_is_charset(**str))
	{
		if (**str == '\'')
		{
			(*str)++;
			while (**str && **str != '\'')
			{
				strs[i][j++] = **str;
				(*str)++;
			}
			(*str)++;
		}
		else if (**str == '\"')
		{
			(*str)++;
			while (**str && **str != '\"')
			{
				strs[i][j++] = **str;
				(*str)++;
			}
			(*str)++;
		}
		else
		{
			strs[i][j++] = **str;
			(*str)++;
		}
	}
	strs[i][j] = '\0';
	return (1);
}

int	handle_delimiters(int i, char **str, char **strs)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup(*str);
	while (tmp[j] && char_is_charset(tmp[j]))
		j++;
	free(tmp);
	tmp = NULL;
	strs[i] = (char *)malloc(sizeof(char) * (j + 1));
	if (!strs[i])
		return (0);
	j = 0;
	while (**str && char_is_delimiter(**str))
	{
		strs[i][j++] = **str;
		(*str)++;
	}
	strs[i][j] = '\0';
	return (1);
}

char	**split_arguments(char *str)
{
	int		words;
	char	**strs;
	int		i;

	words = count_arguments(str);
	if (words == -1)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!char_is_charset(*str))
		{
			if (!handle_words(i, &str, &(*strs)))
				return (NULL);
		}
		else if (char_is_charset(*str))
		{
			if (!handle_delimiters(i, &str, &(*strs)))
				return (NULL);
		}
	}
	strs[i] = NULL;
	return (strs);
}
