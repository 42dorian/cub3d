/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_line_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:41:57 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/20 19:23:06 by dabdulla         ###   ########.fr       */
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

char	*normal_copy(char *original)
{
	int		i;
	char	*new_word;

	i = 0;
	new_word = ft_calloc(sizeof(char), ft_strlen(original) + 1);
	if (!new_word)
		return (NULL);
	while (original[i])
	{
		new_word[i] = original[i];
		i++;
	}
	new_word[i] = NULL_TERMINATOR;
	return (new_word);
}

int	matching_names(char *current_line, char *direction)
{
	if (!ft_strncmp(current_line, direction, 2) && is_end(current_line[2]))
		return (1);
	return (0);
}

int	matching_levels(char *current_line, const char letter)
{
	if (current_line[0] == letter && is_end(current_line[1]))
		return (1);
	return (0);
}
