/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:55:24 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/05 14:55:25 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_cmd_options(char **argv, t_data *data)
{
	int		j;
	int		k;
	char	**options;

	j = data->i;
	k = 0;
	options = NULL;
	if (!argv[++j])
		return (options);
	while (argv[j] && argv[j++][0] == '-')
		k++;
	if (k)
	{
		options = (char **)malloc(sizeof(char *) * (k + 1));
		j = 0;
		while (k--)
			options[j++] = ft_strdup(argv[++data->i]);
		options[j] = NULL;
	}
	return (options);
}

char	**find_cmd_args(char **argv, t_data *data)
{
	int		j;
	int		k;
	char	**args;

	j = data->i;
	k = 0;
	args = NULL;
	if (!argv[++j])
		return (args);
	while (argv[j] && !is_delimiter(argv[j++]))
		k++;
	if (k)
	{
		args = (char **)malloc(sizeof(char *) * (k + 1));
		j = 0;
		while (k--)
			args[j++] = ft_strdup(argv[++data->i]);
		args[j] = NULL;
	}
	return (args);
}
