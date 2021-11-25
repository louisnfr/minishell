/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/25 04:13:20 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_prompt(char **input, t_data *data)
{
	*input = NULL;
	if (isatty(STDIN_FILENO))
	{
		enable_raw_mode(data->sh);
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

char	*safe_getcwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = safe_strdup(data->last_cwd, data);
	else
	{
		if (data->last_cwd)
			clean_free(&data->last_cwd);
		data->last_cwd = safe_strdup(cwd, data);
	}
	return (cwd);
}

char	*get_ret_value(t_data *data)
{
	char	*value;
	char	*ret;

	ret = NULL;
	value = ft_itoa(data->ret_value);
	if (!data->ret_value)
		ret = ft_strjoin_and_free(ret, " \e[0m(\e[32m");
	else
		ret = ft_strjoin_and_free(ret, " \e[0m(\e[31m");
	ret = ft_strjoin_and_free(ret, value);
	ret = ft_strjoin_and_free(ret, "\e[0m)");
	clean_free(&value);
	return (ret);
}

char	*prompt(t_data *data)
{
	char	*usr;
	char	*cwd;
	char	*tmp;
	char	*ret;

	ret = get_ret_value(data);
	usr = get_env("USER", data->env);
	cwd = safe_getcwd(data);
	if (ft_strnstr(cwd, get_env("HOME", data->env),
			ft_strlen(get_env("HOME", data->env))))
	{
		tmp = ft_substr(
				cwd, ft_strlen(get_env("HOME", data->env)), ft_strlen(cwd));
		if (!tmp)
			return ((char *)exit_error_void(NULL, "malloc()", data));
		clean_free(&cwd);
		cwd = safe_strjoin("~", tmp, data);
		clean_free(&tmp);
	}
	usr = safe_strjoin("\e[92m", usr, data);
	usr = safe_strjoin_and_free(usr, "\e[0m:", data);
	usr = safe_strjoin_and_free(usr, "\e[34m", data);
	usr = safe_strjoin_and_free(usr, cwd, data);
	clean_free(&cwd);
	usr = safe_strjoin_and_free(usr, ret, data);
	clean_free(&ret);
	cwd = safe_strjoin_and_free(usr, "\e[0m$ ", data);
	return (cwd);
}
