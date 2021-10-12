#include "minishell.h"

char	**malloc_cmd_array(char **cmd_array, t_cmd *cmd_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_list->options && cmd_list->options[i])
		i++;
	j = 0;
	while (cmd_list->args && cmd_list->args[j++])
		i++;
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		return (NULL);
	return (cmd_array);
}

char	**fill_cmd_array(t_cmd *cmd_list)
{
	char	**cmd_array;
	int		i;
	int		j;

	if (!cmd_list || !cmd_list->command)
		return (NULL);
	cmd_array = NULL;
	cmd_array = malloc_cmd_array(cmd_array, cmd_list);
	if (!cmd_array)
		return (NULL);
	cmd_array[0] = ft_strdup(cmd_list->command);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->options[i]);
		i++;
	}
	j = 0;
	while (cmd_list->args && cmd_list->args[j])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->args[j++]);
		i++;
	}
	cmd_array[++i] = NULL;
	return (cmd_array);
}

t_bool	exec_command(pid_t pid, char **envp, t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;

	(void)data;
	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid == CHILD)
	{
		cmd_array = fill_cmd_array(cmd_list);
		execve(cmd_list->path, cmd_array, envp);
		printf("bash: %s: %s\n", cmd_list->command, strerror(errno));
		return (FAIL);
	}
	else
		wait(NULL);
	return (SUCCESS);
}
