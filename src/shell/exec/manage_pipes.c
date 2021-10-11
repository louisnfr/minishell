#include "minishell.h"

void	exit_error_with_msg(char *error_msg, char *errno_msg, t_data *data)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	if (errno_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errno_msg, 2);
	}
	ft_putchar_fd('\n', 2);
	exec_exit(data->cmd_list, data);
}

void	close_fd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list->next;
	while (cmd)
	{
		if (cmd->input > 2)
			close(cmd->input);
		if (cmd->output > 2)
			close(cmd->output);
		cmd = cmd->next;
	}
}

void	manage_pipes(t_cmd **cmd_list, t_data *data)
{
	printf("%s : in = %d | out = %d\n", (*cmd_list)->command, (*cmd_list)->input, (*cmd_list)->output);
	if (*cmd_list && (*cmd_list)->delimiter != PIPE
		&& (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
	{
		dup2((*cmd_list)->output, 1);
	}	
	else if (*cmd_list && (*cmd_list)->delimiter == PIPE
		&& (*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)
	{
		dup2((*cmd_list)->input, STDIN_FILENO);
		dup2((*cmd_list)->output, STDOUT_FILENO);
	}
	else if (*cmd_list && (*cmd_list)->delimiter == PIPE
		&& (!(*cmd_list)->next || ((*cmd_list)->next && (*cmd_list)->next->delimiter != PIPE)))
	{
		dup2((*cmd_list)->input, 0);
	}
	close_fd(data);
}
