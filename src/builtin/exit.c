/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:27:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/13 20:37:01 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	exit_str_is_digit(char *str)
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

static int	parse_exit_code(char *arg)
{
	unsigned long long	nb;
	int					sign;

	sign = 1;
	if (arg[0] == '-')
		sign = -1;
	nb = ft_atoull(arg);
	if ((sign == 1 && nb > 9223372036854775807)
		|| (sign == -1 && nb > 9223372036854775808uLL))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (nb * sign);
}

static long long	get_exit_code(
	t_bool *quit_exit, t_cmd *cmd_list, t_data *data)
{
	*quit_exit = FALSE;
	if (cmd_list->args && cmd_list->args[0])
	{
		if (exit_str_is_digit(cmd_list->args[0]))
		{
			if (!cmd_list->args[1])
				return (parse_exit_code(cmd_list->args[0]));
			else
			{
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
				data->ret_value = 1;
				*quit_exit = TRUE;
				return (1);
			}
		}
		else
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(cmd_list->args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
	}
	return (data->ret_value);
}

t_bool	exec_exit(t_cmd *cmd_list, t_data *data)
{
	long long	exit_code;
	t_bool		quit_exit;
	t_bool		is_in_pipe;

	is_in_pipe = FALSE;
	if (cmd_list->nb_of_pipes)
		is_in_pipe = TRUE;
	if (isatty(STDIN_FILENO) && !is_in_pipe)
		ft_putstr_fd("exit\n", 2);
	exit_code = get_exit_code(&quit_exit, cmd_list, data);
	if (quit_exit)
		return (EXIT_FAILURE);
	if (is_in_pipe)
	{
		close_all_pipes(&cmd_list, NULL, data);
		close_all_fd(NULL, data);
	}
	clean_data(data);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
