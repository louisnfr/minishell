/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:06:08 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/18 18:57:48 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	cd_error(t_cmd *cmd_list)
{
	ft_putstr_fd("cd: ", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[0], cmd_list->error_output);
	ft_putstr_fd(": No such file or directory\n", cmd_list->error_output);
	return (EXIT_FAILURE);
}

t_bool	cd_error_msg(char *s, t_cmd *cmd_list)
{
	ft_putstr_fd(s, cmd_list->error_output);
	return (EXIT_FAILURE);
}
