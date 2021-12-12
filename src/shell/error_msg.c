/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:43:24 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/12 12:31:24 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_message(char *cmd, char *errno_msg, int fd)
{
	char	*message;

	message = ft_strjoin("bash: ", cmd);
	message = ft_strjoin_and_free(message, ": ");
	message = ft_strjoin_and_free(message, errno_msg);
	message = ft_strjoin_and_free(message, "\n");
	ft_putstr_fd(message, fd);
	clean_free(&message);
}

void	syntax_error_char_msg(int nb, char token)
{
	int	count;

	count = 0;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	while (count++ < nb)
		ft_putchar_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

char	**syntax_error_str_msg(char *token, char **str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	if (str)
		free_double_str(str);
	return (NULL);
}
