/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:52:00 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 20:10:15 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_process_keypress(t_data *data, t_config *sh, t_history *hist, char *delimiter)
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
	(void)data;
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
		c = read_key(sh);
		if (c == ctrl_key('d') && ft_strlen(current) == 0)
		{
			if ((sh->search == sh->h_num && (!current || !ft_strlen(current)))
				|| (sh->search != sh->h_num && (!input || !ft_strlen(input))))
			{
				write(1, "warning: here-document delimited by end-of-file wanted `",
							56);
				write(1, delimiter, ft_strlen(delimiter));
				write(1, "')", 2);
				return (NULL);
			}
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
			write(1, "> ", 2);
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
				cx = 0;
				cx_max = 0;
			}
			else
			{
				k = ft_strlen(input);
				while (k)
					erase_char_history(sh->history, k--, sh->search);
				input = realloc(input, sizeof(char)
						* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
				strcpy(input, find_cmd_history(hist, sh->search));
				cx = 0;
				cx_max = 0;
			}
			write(1, "\x1b[2K", 4);
			write(1, "\x1b[999D", 6);
			write(1, "> ", 2);
		}
		else if (c == DELETE)
		{
			if (cx >= 0 && cx < cx_max)
			{
				if (sh->search == sh->h_num)
				{
					write(1, "\x1b[1C", 4);
					cx++;
					erase_char(current, cx - 1);
					write(1, "\x1b[s", 3);
					write(STDOUT_FILENO, "\x1b[2K", 4);
					write(STDOUT_FILENO, "\x1b[999D", 6);
					write(1, "> ", 2);
					write(1, current, ft_strlen(current));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				else
				{
					write(1, "\x1b[1C", 4);
					cx++;
					write(1, "\x1b[s", 3);
					erase_char_history(sh->history, cx, sh->search);
					input = realloc(input, sizeof(char)
							* (ft_strlen(find_cmd_history(hist,
										sh->search)) + 1));
					strcpy(input, find_cmd_history(hist, sh->search));
					write(STDOUT_FILENO, "\x1b[2K", 4);
					write(STDOUT_FILENO, "\x1b[999D", 6);
					write(1, "> ", 2);
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
					erase_char(current, cx - 1);
					write(1, "\x1b[s", 3);
					write(STDOUT_FILENO, "\x1b[2K", 4);
					write(STDOUT_FILENO, "\x1b[999D", 6);
					write(1, "> ", 2);
					write(1, current, ft_strlen(current));
					write(1, "\x1b[u", 3);
					write(1, "\x1b[1D", 4);
				}
				else
				{
					write(1, "\x1b[s", 3);
					erase_char_history(sh->history, cx, sh->search);
					input = realloc(input, sizeof(char)
							* (ft_strlen(find_cmd_history(hist,
										sh->search)) + 1));
					strcpy(input, find_cmd_history(hist, sh->search));
					write(STDOUT_FILENO, "\x1b[2K", 4);
					write(STDOUT_FILENO, "\x1b[999D", 6);
					write(1, "> ", 2);
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
				write(STDOUT_FILENO, "\x1b[2K", 4);
				write(STDOUT_FILENO, "\x1b[999D", 6);
				write(1, "> ", 2);
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
			write(STDOUT_FILENO, "\x1b[2K", 4);
			write(STDOUT_FILENO, "\x1b[999D", 6);
			write(1, "> ", 2);
			if (next_cmd)
			{
				// printf("check33\n");
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
				// printf("check\n");
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
				write(STDOUT_FILENO, "\x1b[2K", 4);
				write(STDOUT_FILENO, "\x1b[999D", 6);
				write(1, "> ", 2);
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
				write(STDOUT_FILENO, "\x1b[2K", 4);
				write(STDOUT_FILENO, "\x1b[999D", 6);
				write(1, "> ", 2);
				write(1, input, ft_strlen(input));
				write(1, "\x1b[u", 3);
				write(1, "\x1b[1C", 4);
				cx++;
			}
		}
	}
	if (current && sh->search == sh->h_num)
		return (current);
	else if (!current && sh->search == sh->h_num)
	{
		current = ft_strdup("");
		return (current);
	}
	free(current);
	return (input);
}
