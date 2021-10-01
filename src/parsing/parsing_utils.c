#include "minishell.h"

t_bool	is_delimiter(char *str)
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
