/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:04 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/05 15:02:04 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_export(t_cmd *cmd_list, t_data *data)
{
	char	**var;
	int		i;

	i = -1;
	while (cmd_list->args[++i])
	{
		var = ft_split_on_first(cmd_list->args[i], '=');
		add_var(&data->env, new_var(var[0], var[1]));
		free_split(var);
	}
	return (EXIT_SUCCESS);
}
