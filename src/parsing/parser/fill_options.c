/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:13 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 13:21:56 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_cmd_options_end(char **argv, t_data *data)
{
	int		j;
	int		k;
	char	**options;

	k = 0;
	j = data->i;
	options = NULL;
	if (!argv[j])
		return (options);
	while (argv[j] && argv[j++][0] == '-')
		k++;
	if (k)
	{
		options = (char **)ft_calloc(1, sizeof(char *) * (k + 1));
		if (!options)
			exit_error_strs(argv, "malloc()", data);
		j = 0;
		while (k--)
			options[j++] = safe_strdup(argv[data->i++], data);
		options[j] = NULL;
	}
	return (options);
}

char	**find_cmd_options(char **argv, t_data *data)
{
	int		j;
	int		k;
	char	**options;

	k = 0;
	j = data->i;
	options = NULL;
	if (!argv[++j])
		return (options);
	while (argv[j] && argv[j++][0] == '-')
		k++;
	if (k)
	{
		options = (char **)ft_calloc(1, sizeof(char *) * (k + 1));
		if (!options)
			exit_error_strs(argv, "malloc()", data);
		j = 0;
		while (k--)
			options[j++] = safe_strdup(argv[++data->i], data);
		options[j] = NULL;
	}
	return (options);
}
