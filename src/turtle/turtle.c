/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turtle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:07:14 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/09 23:03:54 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_read_key(t_config *sh)
{
	char	seq[3];
	int		nread;
	char	c;

	while (1)
	{
		nread = read(STDIN_FILENO, &c, 1);
		if (nread == -1 && errno != EAGAIN)
			exit_error("read", sh);
		if (nread == 1)
			break ;
	}
	if (c == '\x1b')
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return ('\x1b');
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return ('\x1b');
		if (seq[0] == '[')
		{
			if (seq[1] >= '0' && seq[1] <= '9')
			{
				if (read(STDIN_FILENO, &seq[2], 1) != 1)
					return ('\x1b');
				if (seq[2] == '~')
				{
					switch (seq[1])
					{
						case '3':
							return (DELETE);
					}
				}
			}
			switch (seq[1])
			{
				case 'A':
					return (ARROW_UP);
				case 'B':
					return (ARROW_DOWN);
				case 'C':
					return (ARROW_RIGHT);
				case 'D':
					return (ARROW_LEFT);
			}
		}
		return ('\x1b');
	}
	else
		return (c);
}

char	*shell_process_keypress(t_data *data, t_config *sh, t_history *hist)
{
	char	*input;
	char	*current;
	char	*prev_cmd;
	char	*next_cmd;
	int		cx_min;
	int		cx_max;
	int		cx;
	int		cy;
	char	a;
	int		c;
	int		i;
	int		k;

	(void)cy;
	input = NULL;
	current = NULL;
	i = 0;
	c = 0;
	cx = 0;
	cy = 0;
	cx_min = 0;
	cx_max = cx;
	sh->search = sh->h_num;
	// printf("%d %d\n", sh->h_num, sh->search);
	while (c != 13)
	{
		c = shell_read_key(sh);
		if (c == ctrl_key('d'))
		{
			if (sh->search == sh->h_num && (!current || !ft_strlen(current)))
				exit_free(sh, hist);
			else if (sh->search != sh->h_num && (!input || !ft_strlen(input)))
				exit_free(sh, hist);
		}
		else if (c == ctrl_key('c'))
		{
			free(current);
			free(input);
			write(1, "^C", 2);
			return (NULL);
		}
		else if (c == ctrl_key('l'))
		{
			write(1, "\x1b[s", 3);
			write(1, "\x1b[2J", 4);
			write(1, "\x1b[H", 3);
			write(1, data->prpt, ft_strlen(data->prpt));
			if (current && sh->search == sh->h_num)
				write(1, current, ft_strlen(current));
			else
				write(1, input, ft_strlen(input));
			write(1, "\x1b[u", 3);
			write(1, "\x1b[999A", 6);
		}
		else if (c == ctrl_key('u'))
		{
			if (sh->search == sh->h_num)
			{
				free(current);
				current = NULL;
				clear_prompt(cx, 1);
				cx = 0;
				cx_max = 0;
			}
			else
			{
				k = ft_strlen(input);
				while (k)
					del_char_history(sh->history, k--, sh->search);
				input = realloc(input, sizeof(char)
						* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
				strcpy(input, find_cmd_history(hist, sh->search));
				clear_prompt(cx, 1);
				cx = 0;
				cx_max = 0;
			}
		}
		else if (c == DELETE)
		{
			if (cx >= 0 && cx < cx_max)
			{
				if (sh->search == sh->h_num)
				{
					write(1, "\x1b[1C", 4);
					cx++;
					delete_char(current, cx - 1);
					write(1, "\x1b[s", 3);
					clear_prompt(cx, (int)ft_strlen(current));
					write(1, current, ft_strlen(current));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				else
				{
					write(1, "\x1b[1C", 4);
					cx++;
					write(1, "\x1b[s", 3);
					del_char_history(sh->history, cx, sh->search);
					input = realloc(input, sizeof(char)
							* (ft_strlen(find_cmd_history(hist,
										sh->search)) + 1));
					strcpy(input, find_cmd_history(hist, sh->search));
					clear_prompt(cx, (int)ft_strlen(input));
					write(1, input, ft_strlen(input));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				cx_max--;
				cx--;
			}
		}
		else if (c == BACKSPACE)
		{
			if (cx > 0)
			{
				if (sh->search == sh->h_num)
				{
					delete_char(current, cx - 1);
					write(1, "\x1b[s", 3);
					clear_prompt(cx, (int)ft_strlen(current));
					write(1, current, ft_strlen(current));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				else
				{
					write(1, "\x1b[s", 3);
					del_char_history(sh->history, cx, sh->search);
					input = realloc(input, sizeof(char)
							* (ft_strlen(find_cmd_history(hist,
										sh->search)) + 1));
					strcpy(input, find_cmd_history(hist, sh->search));
					clear_prompt(cx, (int)ft_strlen(input));
					write(1, input, ft_strlen(input));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				cx_max--;
				cx--;
			}
		}
		else if (c == ARROW_LEFT)
		{
			if (cx > cx_min)
			{
				write(1, "\x1b[1D", 4);
				cx--;
			}
		}
		else if (c == ARROW_RIGHT)
		{
			if (cx < cx_max)
			{
				write(1, "\x1b[1C", 4);
				cx++;
			}
		}
		else if (c == ARROW_UP)
		{
			prev_cmd = find_cmd_history(hist, sh->search - 1);
			if (prev_cmd)
			{
				sh->search--;
				if (input)
					free(input);
				input = malloc(sizeof(char) * (ft_strlen(prev_cmd) + 1));
				strcpy(input, prev_cmd);
				clear_prompt(cx, (int)ft_strlen(prev_cmd));
				write(1, input, ft_strlen(input));
				cx = ft_strlen(input);
				cx_max = ft_strlen(input);
			}
		}
		else if (c == ARROW_DOWN)
		{
			if (sh->search == sh->h_num)
				continue ;
			next_cmd = find_cmd_history(hist, sh->search + 1);
			clear_prompt(cx, (int)ft_strlen(next_cmd));
			if (next_cmd)
			{
				if (input)
					free(input);
				input = malloc(sizeof(char) * (ft_strlen(next_cmd) + 1));
				strcpy(input, next_cmd);
				write(1, input, ft_strlen(input));
				cx = ft_strlen(input);
				cx_max = ft_strlen(input);
			}
			else if (!next_cmd)
			{
				free(input);
				input = NULL;
				if (current)
					write(1, current, ft_strlen(current));
				cx = ft_strlen(current);
				cx_max = ft_strlen(current);
			}
			sh->search++;
		}
		else if (ft_isprint(c))
		{
			cx_max++;
			i++;
			a = (char)c;
			if (sh->search == sh->h_num)
			{
				current = insert_char(current, cx, a);
				write(1, "\x1b[s", 3);
				clear_prompt(cx, (int)ft_strlen(current));
				write(1, current, ft_strlen(current));
				write(1, "\x1b[u", 3);
				write(1, "\x1b[1C", 4);
				cx++;
			}
			else
			{
				write(1, "\x1b[s", 3);
				insert_char_history(sh->history, cx, a, sh->search);
				input = realloc(input, sizeof(char)
						* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
				strcpy(input, find_cmd_history(hist, sh->search));
				clear_prompt(cx, (int)ft_strlen(input));
				write(1, input, ft_strlen(input));
				write(1, "\x1b[u", 3);
				write(1, "\x1b[1C", 4);
				cx++;
			}
		}
	}
	if (current && sh->search == sh->h_num)
		return (current);
	free(current);
	return (input);
}
