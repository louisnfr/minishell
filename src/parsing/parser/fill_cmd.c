/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:48:03 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/17 11:56:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return ((char **)exit_error_void(NULL, "malloc()", data));
		j = 0;
		while (k--)
			options[j++] = safe_strdup(argv[++data->i], data);
		options[j] = NULL;
	}
	return (options);
}

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
			return ((char **)exit_error_void(NULL, "malloc()", data));
		j = 0;
		while (k--)
			options[j++] = safe_strdup(argv[data->i++], data);
		options[j] = NULL;
	}
	return (options);
}

static int	get_nb_of_args(char **argv, t_data *data)
{
	int	j;
	int	nb_of_args;

	nb_of_args = 0;
	j = data->i + 1;
	while (argv[j] && !is_delimiter(argv[j])
		&& !is_redirection(argv[j]) && !is_parenthese(argv[j++]))
		nb_of_args++;
	return (nb_of_args);
}

char	**find_cmd_args(char **argv, t_data *data)
{
	int		j;
	int		nb_of_args;
	char	**args;

	args = NULL;
	if (!argv[data->i + 1])
		return (args);
	nb_of_args = get_nb_of_args(argv, data);
	if (nb_of_args)
	{
		args = (char **)ft_calloc(1, sizeof(char *) * (nb_of_args + 1));
		if (!args)
			return ((char **)exit_error_void(NULL, "malloc()", data));
		j = 0;
		while (j < nb_of_args)
		{
			data->i++;
			args[j] = safe_strdup(argv[data->i], data);
			j++;
		}
		args[j] = NULL;
	}
	return (args);
}
