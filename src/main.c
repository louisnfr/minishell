/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/22 18:22:42 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *cmd_list)
{
	if (cmd_list)
	{
		printf("FREE LIST\n");
		free(cmd_list);
		cmd_list = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	char		*input;
	pid_t		pid;
		
	if (ac != 1 || av[1])
		exit(EXIT_FAILURE);
	pid = ft_getpid();
	data = init_data(envp, pid);
	if (!data)
		return (EXIT_FAILURE);
	data->sh = init_config(envp);
	input = NULL;
	while (1)
	{
		clean_free(&data->prpt);
		data->prpt = prompt(data);
		write(1, data->prpt, ft_strlen(data->prpt));
		enable_raw_mode(data->sh);
		input = shell_process_keypress(data, data->sh, data->sh->history);
		disable_raw_mode(data->sh);
		write(1, "\n", 1);
		if (input && ft_strlen(input) > 0)
		{
			add_cmd(&data->sh->history, new_cmd(input, data->sh->h_num));
			data->sh->h_num++;
			init_cmd_list(data);
			if (parse(input, data))
			{
			//	print_list(data->cmd_list);
				exec(data);
			}
			clear_hist(data->sh->history, data->sh->search);
			clean_cmd_list(&data->cmd_list);
			free(data->cmd_list);
			data->cmd_list = NULL;
		}
	}
	return (0);
}
