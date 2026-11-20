/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_line_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:39:20 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/20 19:24:19 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	*create_white_space_set(void)
{
	int		counter;
	int		set_index;
	char	*set;

	counter = BACKSPACE;
	set_index = 0;
	set = ft_calloc(sizeof(char), 8);
	if (!set)
		return (NULL);
	while (counter <= CARRIAGE_RET)
		set[set_index++] = counter++;
	set[set_index++] = SPACE;
	set[set_index] = NULL_TERMINATOR;
	return (set);
}
