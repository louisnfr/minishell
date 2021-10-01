#include "minishell.h"

t_bool	check_heredoc(char *input)
{
	int	i;

	i = 0;
	while (input[i + 1])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_delimiter(char *str)
{
	return (str_is_equal(str, "&&")
		|| str_is_equal(str, ";")
		|| str_is_equal(str, "|")
		|| str_is_equal(str, "||"));
}

int	get_delimiter(char *str)
{
	if (str_is_equal(str, "|"))
		return (PIPE);
	if (str_is_equal(str, "&&"))
		return (AND);
	if (str_is_equal(str, "||"))
		return (OR);
	if (str_is_equal(str, ";"))
		return (SEMICOLON);
	return (0);
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
