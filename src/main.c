/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 10:09:15 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->all_paths = get_paths(envp);
	if (!data->all_paths)
		return (NULL);
	data->i = 0;
	data->pid = 0;
	data->tab_delimiters = ft_strdup("|&;<>");
	update_env(data);
	return (data);
}

t_bool	init_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd *)malloc(sizeof(t_cmd));
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

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	char		*input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data || !ft_getpid(data))
		return (EXIT_FAILURE);
	input = NULL;
	data->sh = init_config(envp);
	while (1)
	{
		data->pr = prompt();
		write(1, data->pr, ft_strlen(data->pr));
		enable_raw_mode(data->sh);
		input = shell_process_keypress(data, data->sh, data->sh->history);
		disable_raw_mode(data->sh);
		write(1, "\n", 1);
		if (input && ft_strlen(input) > 0)
		{
			add_cmd(&data->sh->history, new_cmd(input, data->sh->h_num));
			init_cmd_list(data);
			parse(input, data);
	//		print_list(data->cmd_list);
			exec(envp, data);
			clear_hist(data->sh->history, data->sh->search);
			clean_cmd_list(data->cmd_list);
			data->sh->h_num++;
		}
	}
	return (0);
}
