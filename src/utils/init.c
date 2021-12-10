/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:57 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/10 02:17:13 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == CHILD)
		exit(0);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}

static char	**setup_builtins(t_data *data)
{
	char	**builtins;

	builtins = (char **)ft_calloc(1, sizeof(char *) * 9);
	if (!builtins)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	builtins[0] = safe_strdup("echo", data);
	builtins[1] = safe_strdup("cd", data);
	builtins[2] = safe_strdup("pwd", data);
	builtins[3] = safe_strdup("env", data);
	builtins[4] = safe_strdup("history", data);
	builtins[5] = safe_strdup("export", data);
	builtins[6] = safe_strdup("unset", data);
	builtins[7] = safe_strdup("exit", data);
	builtins[8] = NULL;
	return (builtins);
}

static void	init_var_data(t_data *data)
{
	if (data->all_paths)
		free_double_str(data->all_paths);
	data->all_paths = get_paths(data);
	data->i = 0;
	data->heredoc_failed = FALSE;
	data->pipe_heredoc = NULL;
	data->ret_value = 0;
	data->double_quotes = 1;
	data->redir = NULL;
	data->par_lvl = 0;
	data->to_suppress = NULL;
	data->to_reparse = FALSE;
}

t_data	*init_data(char **envp)
{
	t_data	*data;
	pid_t	pid;

	pid = ft_getpid();
	if (pid == -1)
		return ((t_data *)exit_error_void(NULL, "fork()", NULL));
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return ((t_data *)exit_error_void(NULL, "malloc()", NULL));
	create_update_env(envp, data);
	data->pid = pid;
	data->envp = NULL;
	data->last_cwd = NULL;
	data->env_value = NULL;
	data->builtins = setup_builtins(data);
	init_var_data(data);
	data->cmd_list = NULL;
	data->sh = init_config(envp);
	return (data);
}

t_bool	init_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd_list)
		return (exit_error_bool("malloc()", data));
	setup_cmd_list(data->cmd_list, data);
	init_var_data(data);
	return (SUCCESS);
}
