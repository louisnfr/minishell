/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turtle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:07:14 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 16:39:54 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_arrow_key(char c)
{
	if (c == 'A')
		return (ARROW_UP);
	if (c == 'B')
		return (ARROW_DOWN);
	if (c == 'C')
		return (ARROW_RIGHT);
	if (c == 'D')
		return (ARROW_LEFT);
	return ('\x1b');
}

int	read_escape_seq(void)
{
	char	seq[3];

	if ((read(STDIN_FILENO, &seq[0], 1) != 1)
		|| (read(STDIN_FILENO, &seq[1], 1) != 1))
		return ('\x1b');
	if (seq[0] == '[')
	{
		if (ft_isdigit(seq[1]))
		{
			if (read(STDIN_FILENO, &seq[2], 1) != 1)
				return ('\x1b');
			if (seq[2] == '~')
			{
				if (seq[1] == '3')
					return (DELETE);
			}
		}
		return (read_arrow_key(seq[1]));
	}
	return ('\x1b');
}

int	read_key(t_config *sh)
{
	int		ret;
	char	c;

	while (1)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret == -1 && errno != EAGAIN)
			exit_error("read", sh);
		if (ret == 1)
			break ;
	}
	if (c == '\x1b')
		return (read_escape_seq());
	else
		return (c);
}

void	del_cmd_history(char *input, t_history *history, int search)
{
	int	i;

	i = ft_strlen(input);
	while (i)
		del_char_history(history, i--, search);
}

void	init_shell_values(t_config *sh)
{
	sh->current = NULL;
	sh->input = NULL;
	sh->prev_cmd = NULL;
	sh->next_cmd = NULL;
	sh->cx = 0;
	sh->cy = 0;
	sh->cx_min = 0;
	sh->cx_max = 0;
	sh->search = sh->h_num;
}

t_bool	process_ctrl_key(t_data *data, t_config *sh, t_history *hist, int c)
{
	if (c == ctrl_key('d'))
	{
		if (sh->search == sh->h_num && (!sh->current || !ft_strlen(sh->current)))
			exit_free(sh, hist);
		else if (sh->search != sh->h_num && (!sh->input || !ft_strlen(sh->input)))
			exit_free(sh, hist);
	}
	else if (c == ctrl_key('c'))
	{
		free(sh->current);
		free(sh->input);
		write(1, "^C", 2);
		return (FAIL);
	}
	else if (c == ctrl_key('l'))
	{
		write(1, "\x1b[s", 3);
		write(1, "\x1b[2J", 4);
		write(1, "\x1b[H", 3);
		write(1, data->prpt, ft_strlen(data->prpt));
		if (sh->current && sh->search == sh->h_num)
			write(1, sh->current, ft_strlen(sh->current));
		else
			write(1, sh->input, ft_strlen(sh->input));
		write(1, "\x1b[u", 3);
		write(1, "\x1b[999A", 6);
	}
	else if (c == ctrl_key('u'))
	{
		if (sh->search == sh->h_num)
		{
			free(sh->current);
			sh->current = NULL;
			clear_prompt(sh->cx, 1);
			sh->cx = 0;
			sh->cx_max = 0;
		}
		else
		{
			del_cmd_history(sh->input, sh->history, sh->search);
			sh->input = realloc(sh->input, sizeof(char)
					* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
			strcpy(sh->input, find_cmd_history(hist, sh->search));
			clear_prompt(sh->cx, 1);
			sh->cx = 0;
			sh->cx_max = 0;
		}
	}
	return (SUCCESS);
}

void	process_arrow_key(t_config *sh, t_history *hist, int c)
{
	if (c == ARROW_LEFT)
	{
		if (sh->cx > sh->cx_min)
		{
			write(1, "\x1b[1D", 4);
			sh->cx--;
		}
	}
	else if (c == ARROW_RIGHT)
	{
		if (sh->cx < sh->cx_max)
		{
			write(1, "\x1b[1C", 4);
			sh->cx++;
		}
	}
	else if (c == ARROW_UP)
	{
		sh->prev_cmd = find_cmd_history(hist, sh->search - 1);
		if (sh->prev_cmd)
		{
			sh->search--;
			if (sh->input)
				free(sh->input);
			sh->input = malloc(sizeof(char) * (ft_strlen(sh->prev_cmd) + 1));
			strcpy(sh->input, sh->prev_cmd);
			clear_prompt(sh->cx, (int)ft_strlen(sh->prev_cmd));
			write(1, sh->input, ft_strlen(sh->input));
			sh->cx = ft_strlen(sh->input);
			sh->cx_max = ft_strlen(sh->input);
		}
	}
	else if (c == ARROW_DOWN)
	{
		if (sh->search == sh->h_num)
			return ;
		sh->next_cmd = find_cmd_history(hist, sh->search + 1);
		clear_prompt(sh->cx, (int)ft_strlen(sh->next_cmd));
		if (sh->next_cmd)
		{
			if (sh->input)
				free(sh->input);
			sh->input = malloc(sizeof(char) * (ft_strlen(sh->next_cmd) + 1));
			strcpy(sh->input, sh->next_cmd);
			write(1, sh->input, ft_strlen(sh->input));
			sh->cx = ft_strlen(sh->input);
			sh->cx_max = ft_strlen(sh->input);
		}
		else if (!sh->next_cmd)
		{
			free(sh->input);
			sh->input = NULL;
			if (sh->current)
				write(1, sh->current, ft_strlen(sh->current));
			sh->cx = ft_strlen(sh->current);
			sh->cx_max = ft_strlen(sh->current);
		}
		sh->search++;
	}
}

void	process_del_key(t_config *sh, t_history *hist)
{
	if (sh->cx >= 0 && sh->cx < sh->cx_max)
	{
		if (sh->search == sh->h_num)
		{
			write(1, "\x1b[1C", 4);
			sh->cx++;
			delete_char(sh->current, sh->cx - 1);
			write(1, "\x1b[s", 3);
			clear_prompt(sh->cx, (int)ft_strlen(sh->current));
			write(1, sh->current, ft_strlen(sh->current));
			write(1, "\x1b[u", 3);
			write(1, "\x1b[1D", 4);
		}
		else
		{
			write(1, "\x1b[1C", 4);
			sh->cx++;
			write(1, "\x1b[s", 3);
			del_char_history(sh->history, sh->cx, sh->search);
			sh->input = realloc(sh->input, sizeof(char)
					* (ft_strlen(find_cmd_history(hist,
								sh->search)) + 1));
			strcpy(sh->input, find_cmd_history(hist, sh->search));
			clear_prompt(sh->cx, (int)ft_strlen(sh->input));
			write(1, sh->input, ft_strlen(sh->input));
			write(1, "\x1b[u", 3);
			write(1, "\x1b[1D", 4);
		}
		sh->cx_max--;
		sh->cx--;
	}
}

void	process_backspace_key(t_config *sh, t_history *hist)
{
	if (sh->cx > 0)
	{
		if (sh->search == sh->h_num)
		{
			delete_char(sh->current, sh->cx - 1);
			write(1, "\x1b[s", 3);
			clear_prompt(sh->cx, (int)ft_strlen(sh->current));
			write(1, sh->current, ft_strlen(sh->current));
			write(1, "\x1b[u", 3);
			write(1, "\x1b[1D", 4);
		}
		else
		{
			write(1, "\x1b[s", 3);
			del_char_history(sh->history, sh->cx, sh->search);
			sh->input = realloc(sh->input, sizeof(char)
					* (ft_strlen(find_cmd_history(hist,
								sh->search)) + 1));
			strcpy(sh->input, find_cmd_history(hist, sh->search));
			clear_prompt(sh->cx, (int)ft_strlen(sh->input));
			write(1, sh->input, ft_strlen(sh->input));
			write(1, "\x1b[u", 3);
			write(1, "\x1b[1D", 4);
		}
		sh->cx_max--;
		sh->cx--;
	}
}

void	update_input(t_config *sh, t_history *hist, int c)
{
	sh->cx_max++;
	if (sh->search == sh->h_num)
	{
		sh->current = insert_char(sh->current, sh->cx, (char)c);
		write(1, "\x1b[s", 3);
		clear_prompt(sh->cx, (int)ft_strlen(sh->current));
		write(1, sh->current, ft_strlen(sh->current));
		write(1, "\x1b[u", 3);
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
	else
	{
		write(1, "\x1b[s", 3);
		insert_char_history(sh->history, sh->cx, (char)c, sh->search);
		sh->input = realloc(sh->input, sizeof(char)
				* (ft_strlen(find_cmd_history(hist, sh->search)) + 1));
		strcpy(sh->input, find_cmd_history(hist, sh->search));
		clear_prompt(sh->cx, (int)ft_strlen(sh->input));
		write(1, sh->input, ft_strlen(sh->input));
		write(1, "\x1b[u", 3);
		write(1, "\x1b[1C", 4);
		sh->cx++;
	}
}

char	*send_cmd(t_config *sh)
{
	if (sh->current && sh->search == sh->h_num)
		return (sh->current);
	free(sh->current);
	return (sh->input);
}


char	*shell_process_keypress(t_data *data, t_config *sh, t_history *hist)
{
	int	c;

	c = 0;
	init_shell_values(sh);
	while (c != 13)
	{
		c = read_key(sh);
		if (c == ctrl_key('c') || c == ctrl_key('d')
			|| c == ctrl_key('u') || c == ctrl_key('l'))
		{
			if (!process_ctrl_key(data, sh, hist, c))
				return (NULL);
		}
		else if (c == DELETE)
			process_del_key(sh, hist);
		else if (c == BACKSPACE)
			process_backspace_key(sh, hist);
		else if (c >= ARROW_UP && c <= ARROW_RIGHT)
			process_arrow_key(sh, hist, c);
		else if (ft_isprint(c))
			update_input(sh, hist, c);
	}
	return (send_cmd(sh));
}





/*		TAB HANDLING

struct dirent	*entity;
DIR				*directory;

else if (c == TAB)
		{
			if (sh->current)
			{
				directory = opendir(".");
				entity = readdir(directory);
				while (entity != NULL)
				{
					if (ft_strnstr(entity->d_name, sh->current, (int)ft_strlen(sh->current)))
						break ;
					entity = readdir(directory);
				}
				// printf("found: %s\n", entity->d_name);
				sh->current = realloc(sh->current, (int)ft_strlen(entity->d_name));
				strcpy(sh->current, entity->d_name);
				clear_prompt(sh->cx, 1);
				write(1, sh->current, (int)ft_strlen(sh->current));
				sh->cx = ft_strlen(sh->current);
				sh->cx_max = ft_strlen(sh->current);
				closedir(directory);
			}
		}

*/
