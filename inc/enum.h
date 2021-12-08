/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:20:12 by lraffin           #+#    #+#             */
/*   Updated: 2021/12/08 11:39:29 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef int		t_bool;

typedef enum s_key
{
	BACKSPACE = 127,
	ARROW_UP = 1000,
	ARROW_LEFT,
	ARROW_DOWN,
	ARROW_RIGHT,
	DELETE,
	TAB_KEY = 9,
}	t_key;

typedef enum s_boolean
{
	CHILD	= 0,
	FAIL	= 0,
	SUCCESS = 1,
	CTRL_D	= 2,
	CTRL_C	= 3,
}	t_boolean;

typedef enum s_parenthese
{
	OUT			= 0,
	IN			= 1,
	FIRST		= 2,
	LAST		= 3,
}	t_parenthese;

typedef enum s_flag
{
	WRITE_TRUNC		= 1,
	WRITE_APPEND	= 2,
	READ			= 3,
}	t_flag;

typedef enum s_delimiter
{
	PIPE				= 1,
	AND					= 2,
	OR					= 3,
	SEMICOLON			= 4,
	LEFT_MARK			= 5,
	RIGHT_MARK			= 6,
	DOUBLE_RIGHT_MARK	= 7,
	HEREDOC				= 8,
	ERROR				= 9,
	DOUBLE_ERROR		= 10,
	ERROR_AND_STDOUT	= 11,
	L_PARENTHESE		= 12,
	R_PARENTHESE		= 13,
	AMBIGUOUS_REDIR		= 14,
}	t_delimiter;

#endif
