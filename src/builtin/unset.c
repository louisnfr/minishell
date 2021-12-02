/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:26:58 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/02 10:54:53 by efrancon         ###   ########.fr       */
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

	if (ft_isdigit(s[0]) || s[0] == '=')
		return (FAIL);
	i = -1;
	while (s[++i])
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (FAIL);
	return (SUCCESS);
}

// static void	free_env_var(t_env *var)
// {
// 	clean_free(var->key);
// 	clean_free(var->value);
// 	free(var);
// }

static t_bool	unset(t_env **env, t_cmd *cmd_list)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = -1;
	while (cmd_list->args[++i])
	{
		if (!get_env(cmd_list->args[i], *env))
			return (EXIT_SUCCESS);
		prev = find_prev_var(cmd_list->args[i], *env);
		if (!prev)
		{
			tmp = *env;
			// free_env_var(env);
			*env = tmp->next;
			return (EXIT_SUCCESS);
		}
		prev->next = prev->next->next;
	}
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
	while (cmd_list->args[++i])
	{
		if (!check_unset(cmd_list->args[i]))
			ret = unset_error(cmd_list, i);
		else
		{
			unset(&data->env, cmd_list);
			unset(&data->export, cmd_list);
		}
	}
	return (ret);
}
