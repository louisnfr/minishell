/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:09:53 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 04:16:34 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pos_cursor(int *cx, int *cy)
{
	char			buf[32];
	unsigned int	i;

	i = -1;
	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
		return (-1);
	while (++i < sizeof(buf) - 1)
	{
		if (read(STDIN_FILENO, &buf[i], 1) != 1)
			break ;
		if (buf[i] == 'R')
			break ;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[')
		return (-1);
	if (sscanf(&buf[2], "%d;%d", cy, cx) != 2)
		return (-1);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_config	*sh;
// 	char		*input;

// 	input = NULL;
// 	sh = init_config(envp);
// 	if (ac > 1 || av[1] || !sh)
// 		exit_error("usage error\n", sh);
// 	enable_raw_mode(sh);
// 	while (1)
// 	{
// 		write(1, "\e[32;1mturtle\e[0;1m$ \e[0m", 25);
// 		input = shell_process_keypress(sh, sh->history);
// 		if (input && ft_strlen(input) > 0)
// 		{
// 			add_cmd(&sh->history, new_cmd(input, sh->h_num));
// 			sh->h_num++;
// 		}
// 		clear_hist(sh->history, sh->search);
// 		write(1, "\n", 1);
// 		free(input);
// 	}
// 	return (0);
// }
