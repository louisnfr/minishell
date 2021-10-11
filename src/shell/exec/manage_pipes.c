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

void	close_pipe(t_cmd **cmd_list, t_data *data)
{
	t_cmd	*cmd;

	cmd = *cmd_list;
	printf("cmd_list->cmd = %s\n", cmd->command);
	while (cmd)
	{
		if (cmd->input > 2 && close(cmd->input) == -1)
			exit_error_with_msg("close() failed: ", strerror(errno), data);
		if (cmd->output > 2 && close(cmd->output) == -1)
			exit_error_with_msg("close() failed: ", strerror(errno), data);
		cmd = cmd->next;
	}
}

void	manage_pipes(t_cmd **cmd_list, t_data *data)
{
	(void)data;
	if ((*cmd_list)->input == -1 || (*cmd_list)->output == -1)
		return ;
	if ((*cmd_list)->input != 0)
		dup2((*cmd_list)->input, STDIN_FILENO);
	if ((*cmd_list)->output != 1)
		dup2((*cmd_list)->output, STDOUT_FILENO);
	close_pipe(cmd_list, data);
}
