#include "minishell.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->export = create_env(envp);
	data->i = 0;
	data->pid = 0;
	data->ret_value = 0;
	data->tab_delimiters = ft_strdup("|&;<>");
	update_env(data);
	data->all_paths = get_paths(data);
	if (!data->all_paths)
		return (NULL);
	return (data);
}

t_bool	init_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd_list)
		return (FAIL);
	setup_cmd_list(data->cmd_list);
	if (!create_new_cmd(NULL, NULL, NULL, &data->cmd_list))
		return (FAIL);
	return (SUCCESS);
}

t_bool	ft_getpid(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	if (pid != 0)
		kill(pid, SIGTERM);
	wait(NULL);
	data->pid = pid - 1;
	return (SUCCESS);
}
