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

void	check_ret_value(t_cmd *cmd_list, t_data *data)
{
	int	i;

	i = -1;
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (str_is_equal(cmd_list->args[i], "$?"))
				cmd_list->args[i] = ft_itoa(data->ret_value);
	}
}

void	handle_builtin_cmd(int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*command;
	char	**options;
	char	**args;

	options = NULL;
	args = NULL;
	command = ft_strdup(argv[data->i]);
	if (str_is_equal(command, "echo"))
	{
		if (argv[data->i + 1] && str_is_equal(argv[data->i + 1], "-n"))
		{
			options = (char **)malloc(sizeof(char *) * 2);
			options[0] = ft_strdup(argv[++data->i]);
			options[1] = NULL;
		}
	}
	create_new_cmd(command, options, NULL, &cmd_list);
	cmd_list->is_builtin = TRUE;
	args = find_cmd_args(argv, data);
	cmd_list->args = args;
	if (delimiter)
		cmd_list->delimiter = delimiter;
	check_ret_value(cmd_list, data);
	data->i++;
}

void	handle_other_cmd(int delimiter, char **argv, t_cmd *cmd_list, t_data *data)
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
	check_ret_value(cmd_list, data);
	data->i++;
}

char	**get_argv(char *input)
{
	char	**argv;

	argv = split_arguments(input);
	return (argv);
}

t_bool	parse(char *input, t_data *data)
{
	char	**argv;
	t_cmd	*cmd_list;
	t_bool	is_heredoc;
	int		delimiter;

	delimiter = 0;
	if (!input)
		return (SUCCESS);
	is_heredoc = FALSE;
	if (check_heredoc(input))
		is_heredoc = TRUE;
	cmd_list = data->cmd_list;
	argv = get_argv(input);
	if (!argv)
		return (FAIL);
	data->i = 0;
	while (argv[data->i])
	{
		if (is_delimiter(argv[data->i]))
		{
			delimiter = get_delimiter(argv[data->i]);
			data->i++;
		}
		else if (cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(delimiter, argv, cmd_list, data);
		else
			handle_other_cmd(delimiter, argv, cmd_list, data);
	}
	return (SUCCESS);
}
