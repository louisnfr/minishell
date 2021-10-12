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

int	exec_pipes(pid_t pid, char **envp, t_cmd **cmd_list, t_data *data)
{
	char	**cmd_array;
	int		status;
	int		exit_code;

	exit_code = EXIT_FAILURE;
	while ((*cmd_list) && ((*cmd_list)->delimiter == PIPE
		|| ((*cmd_list)->next && (*cmd_list)->next->delimiter == PIPE)))
	{
		pid = fork();
		if (pid < 0)
			return (FAIL);
		if (pid == CHILD)
		{
			dup2((*cmd_list)->input, STDIN_FILENO);
			dup2((*cmd_list)->output, STDOUT_FILENO);
			close_fd(data);
			cmd_array = fill_cmd_array(*cmd_list);
			execve((*cmd_list)->path, cmd_array, envp);
			printf("bash: %s: %s\n", (*cmd_list)->command, strerror(errno));
			return (FAIL);
		}
		else
			wait(NULL);
		if ((*cmd_list)->input > 2)
			close((*cmd_list)->input);
		if ((*cmd_list)->output > 2)
			close((*cmd_list)->output);
		*cmd_list = (*cmd_list)->next;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}