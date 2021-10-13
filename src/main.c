/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 04:54:34 by lraffin          ###   ########.fr       */
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
	t_data	*data;
	t_config	*sh;
	char		*input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data || !ft_getpid(data))
		return (EXIT_FAILURE);
	input = NULL;
	sh = init_config(envp);
	enable_raw_mode(sh);
	while (1)
	{
		write(1, "\e[32;1mturtle\e[0;1m$ \e[0m", 25);
		input = shell_process_keypress(sh, sh->history);
		write(1, "\n", 1);
		if (input && ft_strlen(input) > 0)
		{
			add_cmd(&sh->history, new_cmd(input, sh->h_num));
			init_cmd_list(data);
			parse(input, data);
			exec(envp, data);
			sh->h_num++;
			clear_hist(sh->history, sh->search);
			clean_cmd_list(data->cmd_list);
		}
		// free(input);
	}
	return (0);
}
