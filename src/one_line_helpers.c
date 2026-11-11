/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_line_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:39:20 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 13:16:04 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char letter)
{
	if (letter == '1')
		return (1);
	return (0);
}

int	is_player(char letter)
{
	if (letter == W || letter == S || letter == N || letter == E)
		return (1);
	return (0);
}

int	is_white_space(char letter)
{
	if ((letter <= CARRIAGE_RET && letter >= BACKSPACE) || letter == SPACE)
		return (1);
	return (0);
}

int	is_null_terminator(char letter)
{
	if (letter == NULL_TERMINATOR)
		return (1);
	return (0);
}
