/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_line_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:41:57 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/12 16:35:58 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_safe_spot(char letter)
{
	if (letter == '1' || letter == 1)
		return (1);
	return (0);
}

int	is_end(char letter)
{
	if (is_white_space(letter) || letter == NULL_TERMINATOR)
		return (1);
	return (0);
}