/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:57:29 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/06 15:55:05 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_str(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = -1;
	while (str && str[++i])
		clean_free(&str[i]);
	free(str);
	str = NULL;
}

static size_t	sizeof_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

static char	**free_tab(char **tabc, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(tabc[i++]);
	free(tabc);
	return (0);
}

static char	**malloc_tabc(int *index, const char *s, char c)
{
	char	**tabc;

	tabc = malloc(sizeof(char *) * 3);
	if (!tabc)
		return (NULL);
	*index = 0;
	tabc[*index] = malloc(sizeof(char) * (sizeof_word(s, c) + 1));
	if (!tabc[*index])
		return (free_tab(tabc, *index));
	return (tabc);
}

char	**ft_split_on_first(const char *s, char c)
{
	char	**tabc;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	tabc = malloc_tabc(&index, s, c);
	if (!tabc)
		return (NULL);
	i = 0;
	while (*s && (*s != c))
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tabc[index])
		return (free_tab(tabc, index));
	i = 0;
	s++;
	while (*s)
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = 0;
	return (tabc);
}

/*
char	**ft_split_on_first(const char *s, char c)
{
	char	**tabc;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	tabc = malloc(sizeof(char *) * 3);
	if (!tabc)
		return (NULL);
	index = 0;
	tabc[index] = malloc(sizeof(char) * (sizeof_word(s, c) + 1));
	if (!tabc[index])
		return (free_tab(tabc, index));
	i = 0;
	while (*s && (*s != c))
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tabc[index])
		return (free_tab(tabc, index));
	i = 0;
	s++;
	while (*s)
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = 0;
	return (tabc);
}
*/