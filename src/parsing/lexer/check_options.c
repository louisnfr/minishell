#include "minishell.h"

static int	handle_quotes(char *quote, char first_char)
{
	if (first_char == '\'' || first_char == '\"')
	{
		*quote = first_char;
		return (2);
	}
	*quote = 0;
	return (1);
}

static t_bool	is_option_echo(char *arg)
{
	int		i;
	char	quote;
	int		ret;

	ret = FAIL;
	if (!arg || (arg[0] && arg[0] != '-'))
		return (FAIL);
	i = 0;
	while (i < (int)ft_strlen(arg))
	{
		i++;
		handle_quotes(&quote, arg[0]);
		if (arg[i] && arg[i] == 'n')
		{
			i++;
			while (arg[i] && arg[i] == 'n')
				i++;
			if (arg[i] && arg[i] != quote)
				break ;
			ret = SUCCESS;
		}
		else
			break ;
	}
	return (ret);
}

static void	reparse_options_and_args(int j, t_cmd *cmd_list, t_data *data)
{
	char	**strs;
	int		i;

	strs = safe_split(cmd_list->args[j], 32, data);
	i = -1;
	while (strs[++i])
	{
		if (!cmd_list->options && is_option_echo(strs[i]))
		{
			cmd_list->options = (char **)ft_calloc(1, sizeof(char *) * 2);
			if (!cmd_list->options)
				exit_error_bool("malloc()", data);
			cmd_list->options[0] = safe_strdup("-n", data);
			cmd_list->options[1] = NULL;
		}
	}
	free_double_str(strs);
}

void	check_options_in_args(t_cmd *cmd_list, t_data *data)
{
	int	i;

	i = -1;
	if (!str_is_equal(cmd_list->command, "echo"))
		return ;
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (str_is_in_str(cmd_list->args[i], "-n"))
		{
			reparse_options_and_args(i, cmd_list, data);
			i = -1;
		}
	}
}
