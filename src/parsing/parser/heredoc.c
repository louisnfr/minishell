/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:58:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/11/06 10:39:40 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_heredoc_delimiter(char *delimiter, t_bool *quotes)
{
	char	*new_delimiter;
	int		i;
	char	charset;
	int		j;

	if (!delimiter || !delimiter[0]
		|| (delimiter[0] && delimiter[0] != '\"' && delimiter[0] != '\''))
		return (delimiter);
	charset = delimiter[0];
	new_delimiter = NULL;
	i = 0;
	j = 0;
	while (delimiter[++i] && delimiter[i] != charset)
		j++;
	new_delimiter = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!new_delimiter)
		return (NULL);
	i = 1;
	j = 0;
	while (delimiter[i] && delimiter[i] != charset)
		new_delimiter[j++] = delimiter[i++];
	new_delimiter[j] = '\0';
	*quotes = 1;
	clean_free(&delimiter);
	return (new_delimiter);
}

void	redir_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	t_bool	quotes;

	quotes = 0;
	cmd_list->heredoc = ft_strjoin(get_env("HOME", data->env), "/heredoc");
	if (!argv[*j])
		return ;
	cmd_list->heredoc_delimiter = parse_heredoc_delimiter(
			ft_strdup(argv[*j]), &quotes);
	read_heredoc(quotes, cmd_list, data);
	cmd_list->input = open(cmd_list->heredoc, O_RDONLY);
	unlink(cmd_list->heredoc);
}

void	handle_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	redir_heredoc(j, argv, cmd_list, data);
	(*j)++;
	if (argv[*j] && str_is_equal(argv[*j], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		(*j)++;
	}
}

void	parse_redirections_heredoc(char **argv, t_cmd *cmd_list, t_data *data)
{
	int	j;
	int	redirection;

	j = data->i;
	redirection = 0;
	while (argv[j] && is_redirection(argv[j]))
	{
		redirection = get_redirection(argv[j]);
		j++;
		if (!argv[j])
			return ;
		if (redirection == HEREDOC)
			handle_heredoc(&j, argv, cmd_list, data);
		else
			j++;
	}
}
