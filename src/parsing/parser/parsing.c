/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/19 19:05:59 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_option_echo(char **argv, t_data *data)
{
	int	j;
	int	ret;
	
	ret = FAIL;
	if (!argv)
		return (FAIL);
	while (argv[++data->i] && argv[data->i][0] == '-')
	{
		j = 1;
		if (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
		{
			j++;
			while (argv[data->i] && argv[data->i][j] && argv[data->i][j] == 'n')
				j++;
			if (argv[data->i][j])
				break;
			ret = SUCCESS;
		}
		else
			break ;
		
	}
	data->i--;
	return (ret);
}

void	handle_builtin_cmd(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*command;
	char	**options;
	char	**args;

	options = NULL;
	args = NULL;
	command = ft_strdup(argv[data->i]);
	if (str_is_equal(command, "echo"))
	{
		if (is_option_echo(argv, data))
		{
			options = (char **)malloc(sizeof(char *) * 2);
			options[0] = ft_strdup("-n");
			options[1] = NULL;
		}
	}
	create_new_cmd(command, options, NULL, &cmd_list);
	cmd_list->is_builtin = TRUE;
	args = find_cmd_args(argv, data);
	cmd_list->args = args;
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
	parse_redirections(argv, cmd_list, data);
}

void	handle_other_cmd(
	int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*command;
	char	*path;
	char	**options;
	char	**args;

	path = NULL;
	options = NULL;
	args = NULL;
	path = find_cmd_path(argv[data->i], data->all_paths);
	command = ft_strdup(argv[data->i]);
	options = find_cmd_options(argv, data);
	create_new_cmd(command, options, path, &cmd_list);
	args = find_cmd_args(argv, data);
	cmd_list->args = args;
	if (delimiter)
		cmd_list->delimiter = delimiter;
	data->i++;
	parse_redirections(argv, cmd_list, data);
}

char	**get_argv(char *input, t_data *data)
{
	char	**argv;

	input = check_input(input);
	if (!input)
		return (NULL);
	input = upgrade_input(input, data);
	argv = split_input(input, data);
	if (!argv)
		return (NULL);
	argv = check_argv(argv);
	if (!argv)
		return (NULL);
		
/*	int i = -1;
	while (argv[++i])
		printf("argv[%d] = %s\n", i, argv[i]);
*/
	clean_free(&input);
	return (argv);
}

t_bool	parse(char *input, t_data *data)
{
	char	**argv;
	t_cmd	*cmd_list;
	int		delimiter;

	if (!input)
		return (SUCCESS);
	delimiter = 0;
	cmd_list = data->cmd_list;
	argv = get_argv(input, data);
	if (!argv)
	{
		data->ret_value = 2;
		return (FAIL);
	}
	data->i = 0;
	while (argv[data->i])
	{
		if (is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
		else
			handle_other_cmd(delimiter, argv, cmd_list, data);
	}
	free_double_str(argv);
	parse_pipes(cmd_list);
	return (SUCCESS);
}