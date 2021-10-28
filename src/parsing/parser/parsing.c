/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:40:26 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/25 14:14:59 by EugenieFran      ###   ########.fr       */
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
			options = (char **)ft_calloc(1, sizeof(char *) * 2);
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
	path = find_cmd_path(argv[data->i], NULL, data->all_paths);
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

void	handle_start_redir(char **argv, t_cmd *cmd_list, t_data *data)
{
	int		fd;
	char	*filename;

	data->i++;
	filename = ft_strdup(argv[data->i]);
	if (argv[data->i] && is_file_name(argv[data->i]))
		fd = open(argv[data->i], O_RDONLY);
	if (!argv[++data->i])
		return ;
	if (cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(0, argv, cmd_list, data);
	else
		handle_other_cmd(0, argv, cmd_list, data);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->redirection = LEFT_MARK;
	cmd_list->input = fd;
	if (cmd_list->input == -1)
		display_error_msg_redir(cmd_list->error_output, filename, strerror(errno));
	clean_free(&filename);
}

char	**get_argv(char *input, t_data *data)
{
	char	**argv;

	input = check_input(input);
	if (!input)
		return (NULL);
	argv = split_input(input, data);
	if (!argv)
	{
		clean_free(&input);
		return (NULL);
	}
	argv = check_argv(argv);
		
/*	int i = -1;
	while (argv[++i])
		printf("argv[%d] = %s\n", i, argv[i]);
*/
	clean_free(&input);
	return (argv);
}

void	fill_parenthese(int parenthese, t_cmd *cmd_list)
{
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	cmd_list->parenthese = parenthese;
}

void	handle_parentheses(char **argv, t_data *data)
{
	t_cmd	*cmd_list;
	int		delimiter;

	delimiter = 0;
	cmd_list = data->cmd_list;
	data->i++;
	if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		handle_builtin_cmd(delimiter, argv, cmd_list, data);
	else if (argv[data->i])
		handle_other_cmd(delimiter, argv, cmd_list, data);	
	fill_parenthese(OPEN, cmd_list);
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
		{
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
			fill_parenthese(IN, cmd_list);
		}
		else if (argv[data->i])
		{
			handle_other_cmd(delimiter, argv, cmd_list, data);
			fill_parenthese(IN, cmd_list);
		}
		if (argv[data->i] && str_is_equal(argv[data->i], ")"))
		{
			fill_parenthese(CLOSE, cmd_list);
			break ;
		}
	}
	data->i++;
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
	if (argv[data->i] && str_is_equal(argv[data->i], "<"))
		handle_start_redir(argv, cmd_list, data);
	while (argv[data->i])
	{
		if (argv[data->i] && is_delimiter(argv[data->i]))
			delimiter = get_delimiter(argv[data->i++]);
		else if (argv[data->i] && str_is_equal(argv[data->i], "("))
		{
			handle_parentheses(argv, data);
		}
		else if (argv[data->i] && cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
		else if (argv[data->i])
			handle_other_cmd(delimiter, argv, cmd_list, data);
	}
	free_double_str(argv);
	parse_pipes(cmd_list);
	return (SUCCESS);
}