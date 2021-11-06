/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:20:12 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/05 16:46:34 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef int	t_bool;

typedef enum s_key
{
	BACKSPACE = 127,
	ARROW_UP = 1000,
	ARROW_LEFT,
	ARROW_DOWN,
	ARROW_RIGHT,
	DELETE,
}	t_key;

typedef enum s_boolean
{
	CHILD	= 0,
	FAIL	= 0,
	SUCCESS = 1,
}	t_boolean;

typedef enum s_parenthese
{
	OUT			= 0,
	IN			= 1,
	FIRST		= 2,
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
}	t_delimiter;

#endif
