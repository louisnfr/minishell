/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:06:08 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 18:45:06 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	cd_error(char *pwd, t_cmd *cmd_list)
{
	ft_putstr("minishell: cd: ");
	perror(cmd_list->args[0]);
	free(pwd);
	return (EXIT_FAILURE);
}
