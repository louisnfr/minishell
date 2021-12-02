/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:58:16 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/02 19:58:27 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*parse_heredoc_delimiter(char *delimiter, t_bool *quotes)
// {
// 	char	*new_delimiter;
// 	int		i;
// 	char	charset;
// 	int		j;

// 	if (!delimiter || !delimiter[0]
// 		|| (delimiter[0] && delimiter[0] != '\"' && delimiter[0] != '\''))
// 		return (delimiter);
// 	charset = delimiter[0];
// 	new_delimiter = NULL;
// 	i = 0;
// 	j = 0;
// 	while (delimiter[++i] && delimiter[i] != charset)
// 		j++;
// 	new_delimiter = (char *)ft_calloc(1, sizeof(char) * (j + 1));
// 	if (!new_delimiter)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (delimiter[i] && delimiter[i] != charset)
// 		new_delimiter[j++] = delimiter[i++];
// 	new_delimiter[j] = '\0';
// 	*quotes = 1;
// 	clean_free(&delimiter);
// 	printf("DELIMITER = %s\n", new_delimiter);
// 	return (new_delimiter);
// }

static char	*parse_heredoc_delimiter(char *delimiter, t_bool *quotes)
{
	char	*new_delimiter;
	int		i;
	int		j;

	if (!delimiter || !delimiter[0]
		|| !(ft_strchr(delimiter, '\"') || ft_strchr(delimiter, '\'')))
		return (delimiter);
	new_delimiter = NULL;
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			i++;
		else
		{
			j++;
			i++;
		}
	}
	new_delimiter = (char *)ft_calloc(1, sizeof(char) * (j + 1));
	if (!new_delimiter)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			i++;
		else
			new_delimiter[j++] = delimiter[i++];
	}
	new_delimiter[j] = '\0';
	*quotes = 1;
	clean_free(&delimiter);
	printf("DELIMITER = %s\n", new_delimiter);
	return (new_delimiter);
}

static void	redir_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	t_bool	quotes;

	quotes = 0;
	cmd_list->heredoc = safe_strjoin(
			get_env("HOME", data->env), "/heredoc", data);
	if (!argv[*j])
		return ;
	// printf("delimiter = %s\n", argv[*j]);
	cmd_list->heredoc_delimiter = parse_heredoc_delimiter(
			safe_strdup(argv[*j], data), &quotes);
	if (!cmd_list->heredoc_delimiter)
		exit_error_bool("malloc()", data);
	read_heredoc(quotes, cmd_list, data);
	cmd_list->input = open(cmd_list->heredoc, O_RDONLY);
	safe_unlink(cmd_list->heredoc, data);
}

static void	handle_heredoc(int *j, char **argv, t_cmd *cmd_list, t_data *data)
{
	redir_heredoc(j, argv, cmd_list, data);
	(*j)++;
	if (argv[*j] && str_is_equal(argv[*j], "2>&1"))
	{
		cmd_list->error_output = cmd_list->output;
		(*j)++;
	}
}

void	parse_redirection_heredoc(char **argv, t_cmd *cmd_list, t_data *data)
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
