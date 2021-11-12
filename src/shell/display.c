/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/12 17:21:15 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_prompt(char **input, t_data *data)
{
	*input = NULL;
	if (enable_raw_mode(data->sh))
	{
		clean_free(&data->prpt);
		data->prpt = prompt(data);
		write(1, data->prpt, ft_strlen(data->prpt));
		*input = shell_process_keypress(data, data->sh, data->sh->history);
		disable_raw_mode(data->sh);
		write(1, "\n", 1);
	}
	else
		*input = readline("minishell> ");
}

char	*prompt(t_data *data)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = get_env("USER", data->env);
	cwd = getcwd(NULL, 0);
	if (ft_strnstr(cwd, get_env("HOME", data->env),
			ft_strlen(get_env("HOME", data->env))))
	{
		tmp = ft_substr(
				cwd, ft_strlen(get_env("HOME", data->env)), ft_strlen(cwd));
		clean_free(&cwd);
		cwd = ft_strjoin("~", tmp);
		clean_free(&tmp);
	}
	usr = ft_strjoin("\e[92;1m", usr);
	usr = ft_strjoin_and_free(usr, "\e[0m:");
	usr = ft_strjoin_and_free(usr, "\e[34;1m");
	usr = ft_strjoin_and_free(usr, cwd);
	clean_free(&cwd);
	cwd = ft_strjoin_and_free(usr, "\e[0m$ ");
	return (cwd);
}
