/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:57 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/07 09:46:06 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_getpid(void)
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

t_data	*init_data(char **envp)
{
	t_data	*data;
	pid_t	pid;

	pid = ft_getpid();
	if (pid == -1)
		return (NULL);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->export = create_env(envp);
	data->i = 0;
	data->pid = pid;
	data->ret_value = 0;
	data->envp = NULL;
	data->tab_delimiters = ft_strdup("|&;<>");
	update_env(data);
	data->all_paths = get_paths(data);
	if (!data->all_paths)
		return (NULL);
	data->cmd_list = NULL;
	return (data);
}

t_bool	init_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd_list)
		return (FAIL);
	setup_cmd_list(data->cmd_list);
	return (SUCCESS);
}
