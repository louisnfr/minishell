#include "minishell.h"

static int	get_length(char *command)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] && (command[i] == '\'' || command[i] == '\"'))
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
			{
				j++;
				i++;
			}
			i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j + 1);
}

char	*remove_quote_command(char *command, t_data *data)
{
	int		i;
	int		j;
	char	quote;
	char	*new_command;

	new_command = (char *)ft_calloc(1, sizeof(char) * get_length(command));
	if (!new_command)
		return ((char *)exit_error_void(NULL, "malloc()", data));
	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] && (command[i] == '\'' || command[i] == '\"'))
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
				new_command[j++] = command[i++];
			i++;
		}
		else
			new_command[j++] = command[i++];
	}
	new_command[j] = '\0';
	clean_free(&command);
	return (new_command);
}

void	recheck_cmd_path(t_cmd **cmd_list, t_data *data)
{
	char	*pid_value;
	char	*ret_value;

	if (!(*cmd_list)->command)
		return ;
	if (!ft_strchr((*cmd_list)->command, '$')
		&& (ft_strchr((*cmd_list)->command, '\"')
			|| ft_strchr((*cmd_list)->command, '\'')))
	{
		(*cmd_list)->command = remove_quote_command((*cmd_list)->command, data);
		(*cmd_list)->path = find_cmd_path(
				(*cmd_list)->command, NULL, data->all_paths, data);
		return ;
	}
	if (!ft_strchr((*cmd_list)->command, '$'))
		return ;
	pid_value = safe_itoa(data->pid, data);
	ret_value = safe_itoa(data->ret_value, data);
	(*cmd_list)->command = transform_str(
			(*cmd_list)->command, pid_value, ret_value, data);
	if (ft_strchr((*cmd_list)->command, 32))
		reparse_command(cmd_list, data);
	(*cmd_list)->path = find_cmd_path(
			(*cmd_list)->command, NULL, data->all_paths, data);
	clean_free(&pid_value);
	clean_free(&ret_value);
}
