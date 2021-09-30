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
	while (argv[j] && argv[j][0] == '-')
	{
		k++;
		j++;
	}
	if (k)
	{
		options = (char **)malloc(sizeof(char *) * k);
		k = 0;
		while (argv[++i] && argv[i][0] == '-')
			options[k++] = ft_strdup(argv[i]);
		options[k] = NULL;
	}
	return (options);
}

t_bool	parse(char *input, t_data *data, t_cmd *cmd_list)
{
	int		i;
	char	*path;
	char	**options;
	char	**argv;

	argv = ft_split(input, ' ');
	if (!argv)
		return (FAIL);
	i = -1;
	while (argv[++i])
	{
		path = NULL;
		options = NULL;
		if (is_separation(argv[i]))
			continue ;
		if (cmd_is_builtin(argv[i]))
		{
			options = find_cmd_options(argv, i);
			create_new_cmd(argv[i], options, NULL, &cmd_list);
			cmd_list->is_builtin = TRUE;
		}
		else
		{
			path = find_cmd_path(argv[i], data->all_paths);
			if (path)
			{
				options = find_cmd_options(argv, i);
				int j = -1;
				while (options && options[++j])
					printf("%s\n", options[j]);
				create_new_cmd(argv[i], options, path, &cmd_list);
			}
		}
	}
	return (SUCCESS);
}
