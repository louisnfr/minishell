/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:01:05 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/13 23:37:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(int nb_of_str, char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (++i < nb_of_str)
	{
		if (args[i])
			clean_free(&(args[i]));
	}
	free(args);
	args = NULL;
}

void	clean_free_double_str(int nb_of_str, t_cmd **cmd_list)
{
	int	i;

	if (!(*cmd_list)->args)
		return ;
	i = -1;
	while (++i < nb_of_str)
	{
		if ((*cmd_list)->args[i])
			clean_free(&((*cmd_list)->args[i]));
	}
	free((*cmd_list)->args);
	(*cmd_list)->args = NULL;
}

void	free_inputs(char **input, t_data *data)
{
	clean_free(input);
	close_all_fd(NULL, data);
	clean_free(&data->sh->current);
	clean_free(&data->sh->input);
}
