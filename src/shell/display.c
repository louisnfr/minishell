/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <lraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:06:40 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/13 20:33:41 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_ret_value(t_data *data)
{
	char	*value;
	char	*ret;

	ret = NULL;
	value = safe_itoa(data->ret_value, data);
	if (!data->ret_value)
		ret = safe_strjoin_and_free2(ret, " \e[0m(\e[32m", data, &value);
	else
		ret = safe_strjoin_and_free2(ret, " \e[0m(\e[31m", data, &value);
	ret = safe_strjoin_and_free2(ret, value, data, &value);
	ret = safe_strjoin_and_free2(ret, "\e[0m)", data, &ret);
	clean_free(&value);
	return (ret);
}

static char	*join_prompt(char *ret, char *usr, char *cwd, t_data *data)
{
	if (!usr)
		usr = "";
	usr = safe_strjoin("\e[92m", usr, data);
	usr = safe_strjoin_and_free2(usr, "\e[0m:", data, &cwd);
	usr = safe_strjoin_and_free2(usr, "\e[34m", data, &cwd);
	usr = safe_strjoin_and_free2(usr, cwd, data, &cwd);
	clean_free(&cwd);
	usr = safe_strjoin_and_free(usr, ret, data);
	clean_free(&ret);
	cwd = safe_strjoin_and_free(usr, "\e[0m$ ", data);
	return (cwd);
}

static char	*adjust_prompt_length(char *cwd, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	int		slash_count;
	int		i;

	slash_count = 0;
	i = count_slash(cwd, &slash_count);
	if (i < 0)
		return (cwd);
	tmp = safe_substr(cwd, ++i, ft_strlen(cwd), data);
	clean_free(&cwd);
	tmp2 = safe_strjoin("..", tmp, data);
	clean_free(&tmp);
	return (tmp2);
}

static char	*prompt(t_data *data)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	data->sh->ret = get_ret_value(data);
	usr = get_env("USER", data->env);
	cwd = safe_getcwd(data);
	if (ft_strnstr(cwd, get_env("HOME", data->env),
			ft_strlen(get_env("HOME", data->env))))
	{
		tmp = safe_substr(cwd, ft_strlen(
					get_env("HOME", data->env)), ft_strlen(cwd), data);
		clean_free(&cwd);
		cwd = safe_strjoin("~", tmp, data);
		clean_free(&tmp);
	}
	cwd = adjust_prompt_length(cwd, data);
	cwd = join_prompt(data->sh->ret, usr, cwd, data);
	return (cwd);
}

void	setup_prompt(char **input, t_data *data)
{
	*input = NULL;
	if (isatty(STDIN_FILENO))
	{
		init_signals(data);
		enable_raw_mode(data->sh);
		clean_free(&data->prpt);
		data->prpt = prompt(data);
		write(1, data->prpt, ft_strlen(data->prpt));
		*input = safe_strdup(
				shell_process_keypress(data, data->sh,
					data->sh->history), data);
		disable_raw_mode(data->sh);
		write(1, "\n", 1);
	}
	else if (get_next_line(STDIN_FILENO, input) <= 0 || !check_gnl(*input))
	{
		clean_free(input);
		if (data)
			clean_data(data);
		exit(0);
	}
}
