/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:37:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/17 13:44:36 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	exec_cmd_bin_in_pipe(t_cmd **cmd_list, t_data *data)
{
	char	**cmd_array;

	close_other_pipes(cmd_list, data);
	if (!is_first_pipe(*cmd_list))
		dup2((*cmd_list)->input, STDIN_FILENO);
	if (!is_last_pipe(*cmd_list))
	{
		dup2((*cmd_list)->output, STDOUT_FILENO);
		dup2((*cmd_list)->error_output, STDERR_FILENO);
	}
	close_pipe(cmd_list, data);
	cmd_array = fill_cmd_array(*cmd_list, data);
	data->envp = env_to_char(data->env, data);
	if (!(*cmd_list)->path)
		return (error_bin_cmd(
				"No such file or directory", 127, *cmd_list, data));
	execve((*cmd_list)->path, cmd_array, data->envp);
	return (error_bin_cmd(strerror(errno), get_error_code(), *cmd_list, data));
}

static void	exec_cmd_in_pipe(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;

	exit_code = EXIT_FAILURE;
	if ((*cmd_list)->is_builtin)
		exit_code = exec_builtin(*cmd_list, data);
	else if ((*cmd_list)->path)
		exec_cmd_bin_in_pipe(cmd_list, data);
	else
	{
		parse_special_value(*cmd_list, data);
		exit_code = (handle_error_cmd_pipe(cmd_list));
	}
	close_all_pipes(cmd_list, data);
	clean_data(data);
	exit(exit_code);
}

void	recursive_piping(int i, pid_t *pid, t_cmd **cmd_list, t_data *data)
{
	int		is_child;

	is_child = create_fork(i, pid, data);
	if (!is_child && *cmd_list && (*cmd_list)->next
		&& (*cmd_list)->next->delimiter == PIPE)
		recursive_piping(++i, pid, &(*cmd_list)->next, data);
	if (is_child)
		exec_cmd_in_pipe(cmd_list, data);
}

int	exec_pipes(t_cmd **cmd_list, t_data *data)
{
	int		exit_code;
	pid_t	*pid;
	int		i;
	int		nb_of_cmd;

	i = 0;
	nb_of_cmd = (*cmd_list)->nb_of_pipes + 1;
	pid = (pid_t *)ft_calloc(1, sizeof(pid_t) * nb_of_cmd);
	if (!pid)
		return (exit_error_bool("malloc()", data));
	exit_code = EXIT_SUCCESS;
	if ((*cmd_list)->path)
		update_path(cmd_list, data);
	recursive_piping(i, pid, cmd_list, data);
	close_cmd_pipes_fd(cmd_list, data);
	i = -1;
	while (++i < nb_of_cmd)
		waitpid(pid[i], &exit_code, 0);
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	free(pid);
	return (exit_code);
}
