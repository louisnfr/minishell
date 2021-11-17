/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/17 02:50:32 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fonction(void)
{
	system("leaks minishell");
}

t_bool	exit_str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && !(str[i] == '+' || str[i] == '-'))
		return (FAIL);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FAIL);
	}
	return (SUCCESS);
}

int	get_exit_code(t_bool *quit_exit, t_cmd *cmd_list, t_data *data)
{
	*quit_exit = FALSE;
	if (cmd_list->args && cmd_list->args[0])
	{
		if (exit_str_is_digit(cmd_list->args[0]))
		{
			if (!cmd_list->args[1])
				return (ft_atoi(cmd_list->args[0]));
			else
			{
				printf("bash: exit: too many arguments\n");
				data->ret_value = 1;
				*quit_exit = TRUE;
				return (1);
			}
		}
		else
		{
			printf("bash: exit: %s: numeric argument required\n",
				cmd_list->args[0]);
			return (2);
		}
	}
	return (data->ret_value);
}

void	exec_exit(t_cmd *cmd_list, t_data *data)
{
	int		exit_code;
	t_bool	quit_exit;

	printf("exit\n");
	exit_code = get_exit_code(&quit_exit, cmd_list, data);
	if (quit_exit)
		return ;
	clean_data(data);
//	atexit(fonction);
	exit(exit_code);
}
