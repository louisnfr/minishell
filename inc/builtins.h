/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:09:28 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/29 19:59:22 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"
# include "enum.h"

t_bool	exec_builtin(t_cmd *cmd_list, t_data *data);

t_bool	exec_echo(t_cmd *cmd_list, t_data *data);

t_bool	exec_cd(t_cmd *cmd_list, t_data *data);
t_bool	ch_dir(char *dir, char *error_msg, t_cmd *cmd_list);
int		get_ret(char *oldpwd, char *cdpath, t_cmd *cmd_list, t_data *data);
t_bool	cd_error(t_cmd *cmd_list);
t_bool	cd_error_msg(char *s, t_cmd *cmd_list);

t_bool	exec_pwd(t_cmd *cmd_list, t_data *data);

t_bool	exec_env(t_cmd *cmd_list, t_data *data);

t_bool	exec_history(t_cmd *cmd_list, t_data *data);

t_bool	exec_export(t_cmd *cmd_list, t_data *data);

t_bool	exec_unset(t_cmd *cmd_list, t_data *data);

t_bool	exec_exit(t_cmd *cmd_list, t_data *data);

#endif
