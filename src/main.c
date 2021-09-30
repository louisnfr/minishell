/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/30 14:57:51 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **envp)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->all_paths = get_paths(envp);
	if (!data->all_paths)
		return (NULL);
	data->cmd_list = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data->cmd_list)
		return (NULL);
	init_cmd_list(data->cmd_list);
	if (!create_new_cmd(NULL, NULL, NULL, &data->cmd_list))
		return (NULL);
	update_env(data);
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		parse(ac, input, data, data->cmd_list);
		print_list(data->cmd_list);
	}
	return (0);
}
