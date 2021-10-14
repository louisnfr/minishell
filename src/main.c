/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/14 17:44:50 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
