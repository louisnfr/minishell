/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:32:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/14 14:59:19 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	char		*input;

	if (ac != 1 || av[1] || !envp || !envp[0])
		return (EXIT_FAILURE);
	data = init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	while (1)
	{
		setup_prompt(&input, data);
		if (input && ft_strlen(input) > 0 && check_raw_input(input))
		{
			add_cmd(&data->sh->history, new_cmd(input, data->sh->h_num, data));
			init_cmd_list(data, input);
			if (parse(input, data))
				exec(data);
			clear_hist(data->sh->history, data->sh->search, data);
			clean_cmd_list(&data->cmd_list, data);
			data->sh->h_num += 1;
		}
		else
			free_inputs(&input, data);
	}
	return (0);
}
