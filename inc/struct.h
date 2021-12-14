/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:18:41 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 10:36:39 by efrancon         ###   ########.fr       */
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
}	t_hist;

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
	DIR					*directory;
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
	char				*ret;
}	t_confg;

typedef struct s_var
{
	int		i;
	int		j;
}	t_var;

typedef struct s_redir
{
	char	**files;
	int		*redirection;
	int		count;
}	t_redir;

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
	int				*redirection;
	char			**files;
	t_bool			redir_error;
	int				parenthese;
	int				par_lvl;
	t_bool			heredoc;
	char			*heredoc_delimiter;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	t_confg	*sh;
	t_cmd	*cmd_list;
	t_env	*env;
	t_env	*export;
	t_redir	*redir;
	char	**all_paths;
	char	*prpt;
	int		ret_value;
	pid_t	pid;
	int		i;
	int		double_quotes;
	char	*env_value;
	char	**builtins;
	char	**envp;
	char	*last_cwd;
	int		par_lvl;
	int		*pipe_heredoc;
	t_bool	heredoc_failed;
	char	*to_suppress;
	t_bool	to_reparse;
	char	**tmp_args;
	char	***argv;
	char	**input;
	char	**pid_str;
	char	**ret_str;
	char	*tmp_path;
	char	*tmp_cmd;
}	t_data;

typedef t_bool	t_op(t_cmd *cmd_list, t_data *data);

#endif
