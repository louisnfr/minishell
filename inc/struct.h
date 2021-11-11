/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:18:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/11 01:37:22 by lraffin          ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_value;
	struct s_env	*next;
}	t_env;

typedef struct s_config
{
	struct termios		orig_termios;
	t_bool				init_termios;
	char				**envp;
	struct s_history	*history;
	char				*input;
	char				*current;
	char				*prev_cmd;
	char				*next_cmd;
	int					h_num;
	int					search;
	int					cx;
	int					cy;
	int					cx_min;
	int					cx_max;
}	t_config;

typedef struct s_var
{
	int		i;
	int		j;
}	t_var;

typedef struct s_cmd
{
	int				input;
	int				output;
	int				error_output;
	int				**pipe_fd;
	int				nb_of_pipes;
	char			*command;
	char			**options;
	char			**args;
	char			*path;
	t_bool			is_builtin;
	int				delimiter;
	int				redirection;
	int				parenthese;
	char			*heredoc;
	char			*heredoc_delimiter;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	t_config	*sh;
	t_cmd		*cmd_list;
	t_env		*env;
	t_env		*export;
	char		**all_paths;
	char		*tab_delimiters;
	char		*prpt;
	int			ret_value;
	pid_t		pid;
	int			i;
	char		**envp;
}	t_data;

#endif
