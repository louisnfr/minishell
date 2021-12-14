/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:31:17 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 13:51:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"
# include "env.h"

/*** create ***/

void	create_update_env(char **envp, t_data *data);

/*** edit ***/

void	set_env(char *key, char *new_value, t_env *env, t_data *data);
void	append_var_env(t_data *data, t_cmd *cmd_list, int i);
void	add_var_env(t_data *data, t_cmd *cmd_list, int i);

/*** list ***/

t_env	*new_var(char *name, char *value, int is_value, t_data *data);
void	add_var(t_env **g_env, t_env *new_var);
t_env	*find_prev_var(char *key, t_env *env);

/*** print ***/

void	print_env(t_env *g_env, t_cmd *cmd_list);
void	print_export(t_cmd *cmd_list, t_data *data);

/*** utils ***/

char	*get_env(char *key, t_env *env);
t_bool	already_exists(char *var, t_env *env);
char	**env_to_char(t_env *env, t_data *data, char **cmd_array);

#endif
