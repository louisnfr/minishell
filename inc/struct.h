/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:18:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 05:49:05 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_history
{
	char				*cmd;
	char				*new;
	struct s_history	*next;
	struct s_history	*previous;
	int					num;
}	t_history;

typedef struct s_config
{
	char				**envp;
	struct s_history	*history;
	int					cx;
	int					cy;
	int					h_num;
	int					search;
	struct termios		orig_termios;
	t_bool				init_termios;
}	t_config;

#endif
