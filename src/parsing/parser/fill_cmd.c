/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/05 15:36:25 by EugenieFran      ###   ########.fr       */
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
		options = (char **)ft_calloc(1, sizeof(char *) * (k + 1));
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
	while (argv[j] && !is_delimiter(argv[j]) && !is_redirection(argv[j])
		&& !is_parenthese(argv[j++]))
		k++;
	if (k)
	{
		args = (char **)ft_calloc(1, sizeof(char *) * (k + 1));
		j = 0;
		while (j < k)
		{
			data->i++;
			args[j] = ft_strdup(argv[data->i]);
			j++;
		}
		args[j] = NULL;
	}
	return (args);
}
