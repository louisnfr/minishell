/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:36:47 by efrancon          #+#    #+#             */
/*   Updated: 2021/10/12 18:36:52 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_redirection(int delimiter)
{
	return (delimiter == LEFT_MARK || delimiter == HEREDOC
		|| delimiter == RIGHT_MARK || delimiter == DOUBLE_RIGHT_MARK);
}

void	handle_redirection(int delimiter, t_cmd *cmd_list)
{
	(void)delimiter;
	(void)cmd_list;
}

