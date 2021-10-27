/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:18:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/26 22:19:30 by EugenieFran      ###   ########.fr       */
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
	char				**envp;
	struct s_history	*history;
	int					cx;
	int					cy;
	int					h_num;
	int					search;
	struct termios		orig_termios;
	t_bool				init_termios;
}	t_config;

typedef struct s_cmd
{
	int				input;
	int				output;
	int				error_output;
	char			*command;
	char			**options;
	char			**args;
	char			*path;
	t_bool			is_builtin;
	int				delimiter;
	int				redirection;
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
	pid_t		pipe_pid;
	t_bool		is_parent;
}	t_data;

#endif
