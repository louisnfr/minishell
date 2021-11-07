/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:32:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/07 09:53:27 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_prompt(char **input, t_data *data)
{
	*input = NULL;
	clean_free(&data->prpt);
	data->prpt = prompt(data);
	write(1, data->prpt, ft_strlen(data->prpt));
	enable_raw_mode(data->sh);
	*input = shell_process_keypress(data, data->sh, data->sh->history);
	disable_raw_mode(data->sh);
	write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	char		*input;

	if (ac != 1 || av[1])
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	data->sh = init_config(envp);
	while (1)
	{
		setup_prompt(&input, data);
		if (input && ft_strlen(input) > 0)
		{
			add_cmd(&data->sh->history, new_cmd(input, data->sh->h_num));
			data->sh->h_num++;
			init_cmd_list(data);
			if (parse(input, data))
				exec(data);
	//		print_list(data->cmd_list);
			clear_hist(data->sh->history, data->sh->search);
			clean_cmd_list(&data->cmd_list);
		}
	}
	return (0);
}
