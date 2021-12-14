/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:47:29 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/14 13:51:53 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *key, char *new_value, t_env *env, t_data *data)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			break ;
		env = env->next;
	}
	env->is_value = 1;
	clean_free(&env->value);
	env->value = ft_calloc(1, sizeof(char) + (ft_strlen(new_value) + 1));
	if (!env->value)
	{
		clean_free(&new_value);
		exit_error_str(NULL, "malloc()", data);
	}
	if (new_value)
		ft_memcpy(env->value, new_value, ft_strlen(new_value) + 1);
	env = head;
}

static void	append_env(char *key, char *new_value, t_env *env, t_data *data)
{
	t_env	*head;
	char	*var;
	char	*dest;

	head = env;
	var = get_env(key, data->export);
	dest = ft_calloc(ft_strlen(var) + ft_strlen(new_value) + 1, sizeof(char));
	if (!dest)
		exit_error_str(NULL, "malloc()", data);
	ft_strcat(dest, var);
	ft_strcat(dest, new_value);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			break ;
		env = env->next;
	}
	env->is_value = 1;
	clean_free(&env->value);
	env->value = ft_calloc((ft_strlen(dest) + 1), sizeof(char));
	if (!env->value)
		exit_error_str(NULL, "malloc()", data);
	ft_memcpy(env->value, dest, ft_strlen(dest) + 1);
	clean_free(&dest);
	env = head;
}

void	append_var_env(t_data *data, t_cmd *cmd_list, int i)
{
	char	**var;

	var = safe_split_on_first(cmd_list->args[i], '=', data);
	var[0] = ft_strtrim(var[0], "+");
	if (!already_exists(var[0], data->env))
		add_var(&data->env, new_var(var[0], var[1], 1, data));
	else
		append_env(var[0], var[1], data->env, data);
	if (!already_exists(var[0], data->export))
		add_var(&data->export, new_var(var[0], var[1], 1, data));
	else
		append_env(var[0], var[1], data->export, data);
	free_split(var);
}

void	add_var_env(t_data *data, t_cmd *cmd_list, int i)
{
	char	**var;

	var = safe_split_on_first(cmd_list->args[i], '=', data);
	var[0] = ft_strtrim(var[0], "+");
	if (!already_exists(var[0], data->env))
		add_var(&data->env, new_var(var[0], var[1], 1, data));
	else
		set_env(var[0], var[1], data->env, data);
	if (!already_exists(var[0], data->export))
		add_var(&data->export, new_var(var[0], var[1], 1, data));
	else
		set_env(var[0], var[1], data->export, data);
	free_split(var);
}
