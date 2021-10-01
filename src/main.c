/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/01 19:58:29 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios tty_attr_old;
struct termios tty_attr;
int old_keyboard_mode;

int init_terminal()
{
	/* init terminal device to raw mode */
	if (ioctl(0, KDGKBMODE, &old_keyboard_mode) < 0)
	{
		/* this usually happens when X is running */
		/* Print some error and exit              */
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, &tty_attr_old);
	tty_attr = tty_attr_old;
	/* turn off buffering, echo and key processing */
	tty_attr.c_lflag &= ~(ICANON | ECHO | ISIG);
	tty_attr.c_iflag &= ~(ISTRIP | INLCR | ICRNL |
						  IGNCR | IXON | IXOFF);
	/* block until 1 key comes in */
	tty_attr.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &tty_attr);
	ioctl(0, KDSKBMODE, K_RAW);
	printf("check\n");
	return 1;
}

void exit_gracefully(int stat)
{
	tcsetattr(0, TCSAFLUSH, &tty_attr_old);
	ioctl(0, KDSKBMODE, old_keyboard_mode);
	exit(stat);
}

t_data *init_data(char **envp)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = create_env(envp);
	data->all_paths = get_paths(envp);
	if (!data->all_paths)
		return (NULL);
	data->i = 0;
	update_env(data);
	return (data);
}

t_bool init_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data->cmd_list)
		return (FAIL);
	setup_cmd_list(data->cmd_list);
	if (!create_new_cmd(NULL, NULL, NULL, &data->cmd_list))
		return (FAIL);
	return (SUCCESS);
}

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;

	// init_terminal();
	// exit_gracefully(0);
	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		init_cmd_list(data);
		parse(input, data);
		exec(envp, data);
		//	print_list(data->cmd_list);
		clean_cmd_list(data->cmd_list);
	}
	return (0);
}
