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

t_data	*init_data()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data();
	data->env = create_env(envp);
	update_env(data);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		parse(input, data);
	}
	return (0);
}
