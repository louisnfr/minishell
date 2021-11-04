/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:28 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/04 14:36:30 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_cmd_array(char **cmd_array, t_cmd *cmd_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_list->options && cmd_list->options[i])
		i++;
	j = 0;
	while (cmd_list->args && cmd_list->args[j])
	{
		if (ft_strchr(cmd_list->args[j], '*'))
			count_wildcard_arg(&i, cmd_list->args[j]);
		else
			i++;
		j++;
	}
	cmd_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd_array)
		return (NULL);
	return (cmd_array);
}

void	fill_args(char **cmd_array, int *i, t_cmd *cmd_list, t_data *data)
{
	int		j;
	char	*ret_value;

	j = 0;
	ret_value = ft_itoa(data->ret_value);
	while (cmd_list->args && cmd_list->args[j])
	{
		if (ft_strchr(cmd_list->args[j], '*'))
			fill_wildcard_arg(&(*cmd_array), i, cmd_list->args[j]);
		else
		{
			cmd_array[*i + 1] = ft_strdup(cmd_list->args[j]);
			(*i)++;
		}
		j++;
	}
	clean_free(&ret_value);
}

char	**fill_cmd_array(t_cmd *cmd_list, t_data *data)
{
	char	**cmd_array;
	int		i;

	if (!cmd_list || !cmd_list->command)
		return (NULL);
	cmd_array = NULL;
	cmd_array = malloc_cmd_array(cmd_array, cmd_list);
	if (!cmd_array)
		return (NULL);
	parse_special_value(cmd_list, data);
	cmd_array[0] = ft_strdup(cmd_list->command);
	i = 0;
	while (cmd_list->options && cmd_list->options[i])
	{
		cmd_array[i + 1] = ft_strdup(cmd_list->options[i]);
		i++;
	}
	fill_args(&(*cmd_array), &i, cmd_list, data);
	cmd_array[++i] = NULL;
	return (cmd_array);
}
