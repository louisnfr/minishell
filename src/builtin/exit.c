/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/15 15:25:35 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fonction(void)
{
	system("leaks minishell");
}

/*
void	exec_exit(t_cmd *cmd_list, t_data *data)
{
	(void)cmd_list;
	// write(1, "exit\n", 6);
	// free_split(cmd);
	// free data
	printf("exit\n");
	disable_raw_mode(data->sh);
	free_history(data->sh->history);
	free(data->sh);
	clean_data(data);
	// atexit(fonction);
	exit(data->ret_value);
}
*/

t_bool	str_is_digit(char *str)
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

int	get_exit_code(t_cmd *cmd_list, t_data *data, t_bool *quit_exit)
{
	int	exit_code;

	exit_code = 0;
	if (cmd_list->args && cmd_list->args[0])
	{
		if (str_is_digit(cmd_list->args[0]))
		{
			if (!cmd_list->args[1])
				exit_code = ft_atoi(cmd_list->args[0]);
			else
			{
				printf("bash: exit: too many arguments\n");
				data->ret_value = 1;
				*quit_exit = TRUE;
			}
		}
		else
		{
			printf("bash: exit: %s: numeric argument required\n", cmd_list->args[0]);
			exit_code = 2;
		}
	}
	else
		exit_code = data->ret_value;
	return (exit_code);
}

void	exec_exit(t_cmd *cmd_list, t_data *data)
{
	int		exit_code;
	t_bool	quit_exit;
	
	printf("exit\n");
	quit_exit = FALSE;
	exit_code = get_exit_code(cmd_list, data, &quit_exit);
	if (quit_exit)
		return ;
	disable_raw_mode(data->sh);
	free_history(data->sh->history);
	free(data->sh);
	clean_data(data);
	// atexit(fonction);
	exit(exit_code);
}
