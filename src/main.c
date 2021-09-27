/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:36:22 by lraffin           #+#    #+#             */
/*   Updated: 2021/09/28 00:25:10 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

char	*get_user(void)
{
	char	*usr;
	int		i;

	i = 0;
	while (!ft_strnstr(g_env[i], "USER", 4))
		i++;
	usr = g_env[i] + 5;
	return (usr);
}

void	prompt(void)
{
	char	*usr;
	char	*cwd;
	char	*tmp;

	usr = get_user();
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("/home/", usr);
	if (ft_strnstr(cwd, tmp, ft_strlen(cwd)))
	{
		free(tmp);
		tmp = ft_substr(cwd, 6 + ft_strlen(usr), ft_strlen(cwd));
	}
	free(cwd);
	cwd = ft_strjoin("~", tmp);
	free(tmp);
	ft_putstr_fd("\e[32;1m", 1);
	ft_putstr_fd(usr, 1);
	ft_putstr_fd("\e[0m:", 1);
	ft_putstr_fd("\e[36;1m", 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("$ \e[0m", 1);
	free(cwd);
}

void	extract(char *input, char **env)
{
	(void)env;
	if (!ft_strcmp(input, "exit"))
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
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
		extract(input, env);
		free(input);
	}
	return (0);
}
