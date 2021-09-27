/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 01:15:56 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

char	*get_env(char *arg)
{
	char	*ret;
	int		i;

	i = 0;
	while (!ft_strnstr(g_env[i], arg, ft_strlen(arg)))
		i++;
	ret = g_env[i] + ft_strlen(arg) + 1;
	return (ret);
}

void	prompt(void)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = get_env("USER");
	cwd = getcwd(NULL, 0);
	if (ft_strnstr(cwd, get_env("HOME"), ft_strlen(get_env("HOME"))))
	{
		tmp = ft_substr(cwd, 6 + ft_strlen(usr), ft_strlen(cwd));
		free(cwd);
		cwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	ft_putstr_fd("\e[32;1m", 1);
	ft_putstr_fd(usr, 1);
	ft_putstr_fd("\e[0m:", 1);
	ft_putstr_fd("\e[36;1m", 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("$ \e[0m", 1);
	free(cwd);
}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}

void	extract(char *input)
{
	char	**cmd;
	// char	*tmp;

	cmd = ft_split(input, 32);

	if (!ft_strcmp(cmd[0], "/bin/ls"))
	{
		execve(cmd[0], cmd, g_env);
		// quitte le process
	}

	if (!ft_strcmp(cmd[0], "cd"))
	{
		if (!cmd[1])
			chdir(get_env("HOME"));
		else
			chdir(cmd[1]);
	}

	if (!ft_strcmp(input, "exit"))
	{
		free(input);
		free_split(cmd);
		exit(EXIT_SUCCESS);
	}
	free_split(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)av;
	g_env = env;
	if (ac != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		extract(input);
		free(input);
	}
	return (0);
}
