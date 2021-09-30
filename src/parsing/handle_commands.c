#include "minishell.h"

char	**fill_cmd_array(t_cmd *cmd_list)
{
	int		i;
	char	**cmd_array;
	int		options_length;

	if (!cmd_list->command)
		return (NULL);
	i = 0;
	while (cmd_list->options[i])
		i++;
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		exit_error(cmd_list, EXIT_FAILURE);
	cmd_array[0] = cmd_list->command;
	i = -1;
	while (cmd_list->options[++i])
		cmd_array[i + 1] = cmd_list->options[i];
	cmd_array[++i] = NULL;
	return (cmd_array);
}

void	execute_command(char **envp, t_cmd *cmd_list)
{
	if (cmd_list->is_builtin)
	{
		// execute_buitin(cmd_list->command, cmd_list->options);
	}
	else if (cmd_list->path)
	{
		execve(cmd_list->path, fill_cmd_array(cmd_list), envp);
		exit_error_with_msg("execve() failed: ", strerror(errno), cmd_list);
	}
	exit_error(cmd_list, 127);
}

int	handle_commands(char **envp, t_cmd *cmd_list)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	exit_code = EXIT_FAILURE;
	while (cmd_list)
	{
		pid = fork();
		if (pid < 0)
			exit_error_with_msg("fork() failed: ", strerror(errno), cmd_list);
		if (pid == CHILD)
			execute_command(envp, cmd_list);
		cmd_list = cmd_list->left;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}
