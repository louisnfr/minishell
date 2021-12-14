/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:57 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 10:20:49 by efrancon         ###   ########.fr       */
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
		exit_error_str(NULL, "malloc()", data);
	builtins[0] = safe_strdup_free("echo", data, builtins);
	builtins[1] = safe_strdup_free("cd", data, builtins);
	builtins[2] = safe_strdup_free("pwd", data, builtins);
	builtins[3] = safe_strdup_free("env", data, builtins);
	builtins[4] = safe_strdup_free("history", data, builtins);
	builtins[5] = safe_strdup_free("export", data, builtins);
	builtins[6] = safe_strdup_free("unset", data, builtins);
	builtins[7] = safe_strdup_free("exit", data, builtins);
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
	data->double_quotes = 1;
	data->redir = NULL;
	data->par_lvl = 0;
	data->to_suppress = NULL;
	data->to_reparse = FALSE;
	data->tmp_args = NULL;
	data->argv = NULL;
	data->input = NULL;
	data->pid_str = NULL;
	data->ret_str = NULL;
	data->tmp_path = NULL;
	data->tmp_cmd = NULL;
}

t_data	*init_data(char **envp)
{
	t_data	*data;
	pid_t	pid;

	pid = ft_getpid();
	if (pid == -1)
		exit(1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(1);
	create_update_env(envp, data);
	data->pid = pid;
	data->ret_value = 0;
	data->envp = NULL;
	data->last_cwd = NULL;
	data->env_value = NULL;
	data->builtins = setup_builtins(data);
	init_var_data(data);
	data->cmd_list = NULL;
	data->sh = init_config(envp);
	return (data);
}

t_bool	init_cmd_list(t_data *data, char *input)
{
	data->cmd_list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd_list)
		exit_error_str(input, "malloc()", data);
	setup_cmd_list(data->cmd_list, data);
	init_var_data(data);
	return (SUCCESS);
}
