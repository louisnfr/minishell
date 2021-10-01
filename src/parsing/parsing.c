#include "minishell.h"

t_bool	is_separation(char *str)
{
	return (str_is_equal(str, "&&")
		|| str_is_equal(str, ";")
		|| str_is_equal(str, "|")
		|| str_is_equal(str, "||"));
}

t_bool	cmd_is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	builtins[7] = NULL;
	i = -1;
	while (builtins[++i])
	{
		if (str_is_equal(cmd, builtins[i]))
			return (TRUE);
	}
	return (FALSE);
}

char	**find_cmd_options(char **argv, int i)
{
	int		j;
	int		k;
	char	**options;

	j = i;
	k = 0;
	options = NULL;
	if (!argv[++j])
		return (options);
	while (argv[j] && argv[j++][0] == '-')
		k++;
	if (k)
	{
		options = (char **)malloc(sizeof(char *) * (k + 1));
		k = 0;
		while (argv[++i] && argv[i][0] == '-')
			options[k++] = ft_strdup(argv[i]);
		options[k] = NULL;
	}
	return (options);
}

void	handle_builtin_cmd(int i, char **argv, t_cmd *cmd_list)
{
	char	**options;

	options = NULL;
	options = find_cmd_options(argv, i);
	create_new_cmd(argv[i], options, NULL, &cmd_list);
	cmd_list->is_builtin = TRUE;
}

void	handle_other_cmd(int i, char **argv, t_cmd *cmd_list, t_data *data)
{
	char	*path;
	char	**options;

	path = NULL;
	options = NULL;
	path = find_cmd_path(argv[i], data->all_paths);
	if (path)
	{
		options = find_cmd_options(argv, i);
		create_new_cmd(argv[i], options, path, &cmd_list);
	}
}

t_bool	parse(char *input, t_data *data)
{
	int		i;
	char	**argv;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	argv = ft_split(input, ' ');
	if (!argv)
		return (FAIL);
	i = -1;
	while (argv[++i])
	{
		if (is_separation(argv[i]))
			continue ;
		if (cmd_is_builtin(argv[i]))
			handle_builtin_cmd(i, argv, cmd_list);
		else
			handle_other_cmd(i, argv, cmd_list, data);
	}
	return (SUCCESS);
}
