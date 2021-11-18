/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:49 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/25 11:38:10 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exec_pwd(t_cmd *cmd_list, t_data *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		perror(pwd);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, cmd_list->output);
	ft_putchar_fd('\n', cmd_list->output);
	clean_free(&pwd);
	return (EXIT_SUCCESS);
}
