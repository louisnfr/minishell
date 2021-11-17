/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:32:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/17 02:45:59 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	char		*input;

	char *s = "1234?";
	printf("ret: %d\n", str_is_digit(s));
	exit(0);

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
