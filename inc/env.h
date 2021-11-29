/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:31:17 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:57:50 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"
# include "env.h"

/*** create ***/

t_env	*new_var(char *name, char *value, int is_value);

/*** edit ***/

void	set_env(char *key, char *new_value, t_env *env, t_data *data);
void	append_env(char *key, char *new_value, t_env *env, t_data *data);
void	append_var_env(t_data *data, t_cmd *cmd_list, int i);

/*** env ***/

t_env	*find_prev_var(char *key, t_env *env);
void	add_var_env(t_data *data, t_cmd *cmd_list, int i);
void	create_update_env(char **envp, t_data *data);
int		get_env_size(t_env *env);
char	**env_to_char(t_env *env, t_data *data);
// t_env	*dup_env(char **envp, t_data *data);
void	update_env(t_data *data, t_env *env);
char	*get_env(char *key, t_env *env);
t_env	*get_last(t_env *g_env);
void	add_var(t_env **g_env, t_env *new_var);

/*** print ***/

void	print_env(t_env *g_env, t_cmd *cmd_list);
void	print_export(t_cmd *cmd_list, t_data *data);

/*** list ***/

/*** utils ***/

t_bool	already_exists(char *var, t_env *env);

#endif
