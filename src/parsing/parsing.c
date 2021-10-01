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

void	handle_builtin_cmd(char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*command;
	char	**options;
	char	**args;

	options = NULL;
	args = NULL;
	command = ft_strdup(argv[data->i]);
	options = find_cmd_options(argv, data);
	create_new_cmd(command, options, NULL, &cmd_list);
	cmd_list->is_builtin = TRUE;
	if (str_is_equal(command, "echo"))
	{
		args = find_cmd_args(argv, data);
		cmd_list->args = args;
	}
	data->i++;
}

void	handle_other_cmd(char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*command;
	char	*path;
	char	**options;
	char	**args;

	path = NULL;
	options = NULL;
	args = NULL;
	path = find_cmd_path(argv[data->i], data->all_paths);
	if (path)
	{
		command = ft_strdup(argv[data->i]);
		options = find_cmd_options(argv, data);
		create_new_cmd(command, options, path, &cmd_list);
	}
	args = find_cmd_args(argv, data);
	cmd_list->args = args;
	data->i++;
}

t_bool	parse(char *input, t_data *data)
{
	char	**argv;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	argv = ft_split(input, ' ');
	if (!argv)
		return (FAIL);
	data->i = 0;
	while (argv[data->i])
	{
		if (is_delimiter(argv[data->i]))
			data->i++;
		else if (cmd_is_builtin(argv[data->i]))
			handle_builtin_cmd(argv, cmd_list, data);
		else
			handle_other_cmd(argv, cmd_list, data);
	}
	return (SUCCESS);
}
