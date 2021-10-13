/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:20:12 by lraffin           #+#    #+#             */
/*   Updated: 2021/10/13 05:49:00 by lraffin          ###   ########.fr       */
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

#endif
