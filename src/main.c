/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/06 17:47:36 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data(char **envp)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->all_paths = get_paths(envp);
	if (!data->all_paths)
		return (NULL);
	data->i = 0;
	data->pid = 0;
	update_env(data);
	return (data);
}

t_bool init_cmd_list(t_data *data)
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

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		ft_putstr(prompt());
		signal(SIGINT, sig_handler);
	}
}

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data || !ft_getpid(data))
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, sig_handler);
		input = readline(prompt());
		add_history(input);
		init_cmd_list(data);
		parse(input, data);
		exec(envp, data);
	//	print_list(data->cmd_list);
		clean_cmd_list(data->cmd_list);
	}
	return (0);
}
