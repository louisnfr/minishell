/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/07 19:09:33 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_error(t_cmd *cmd_list, int i)
{
	ft_putstr_fd("unset: `", cmd_list->error_output);
	ft_putstr_fd(cmd_list->args[i], cmd_list->error_output);
	ft_putstr_fd("': not a valid identifier\n", cmd_list->error_output);
	return (EXIT_FAILURE);
}

static t_bool	check_unset(char *s)
{
	int	i;

	if (s && !ft_strlen(s))
		return (FAIL);
	if (ft_isdigit(s[0]) || s[0] == '=')
		return (FAIL);
	i = -1;
	while (s[++i])
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (FAIL);
	return (SUCCESS);
}

static void	free_env_var(t_env *var)
{
	clean_free(&var->key);
	clean_free(&var->value);
	free(var);
	var = NULL;
}

static t_bool	unset(t_env **env, char *var)
{
	t_env	*prev;
	t_env	*tmp;

	if (!get_env(var, *env))
		return (EXIT_SUCCESS);
	prev = find_prev_var(var, *env);
	if (!prev)
	{
		tmp = *env;
		*env = (*env)->next;
		free_env_var(tmp);
		return (EXIT_SUCCESS);
	}
	tmp = prev->next;
	prev->next = prev->next->next;
	free_env_var(tmp);
	return (EXIT_SUCCESS);
}

t_bool	exec_unset(t_cmd *cmd_list, t_data *data)
{
	int	ret;
	int	i;

	ret = EXIT_SUCCESS;
	if (!cmd_list->args || !cmd_list->args[0])
		return (EXIT_SUCCESS);
	if (cmd_list && cmd_list->next && cmd_list->next->delimiter == PIPE)
		return (EXIT_SUCCESS);
	i = -1;
	while (cmd_list->args && cmd_list->args[++i])
	{
		if (!check_unset(cmd_list->args[i]))
			ret = unset_error(cmd_list, i);
		else
		{
			unset(&data->env, cmd_list->args[i]);
			unset(&data->export, cmd_list->args[i]);
		}
	}
	return (ret);
}
