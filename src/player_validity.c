/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 13:12:08 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 23:36:33 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_player(char letter, int *news, int *exit_code)
{
	if (is_player(letter))
	{
		if (*news)
		{
			*exit_code = 1;
			return (0);
		}
		else
			*news = letter;
	}
	else if (letter != ONE && letter != ZERO && !is_white_space(letter))
	{
		*exit_code = 2;
		return (0);
	}
	return (1);
}

int	player_check(char **map, int *exit_code)
{
	int	news;
	int	i;
	int	j;

	news = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (!valid_player(map[i][j], &news, exit_code))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	if (!news)
	{
		*exit_code = 5;
		return (0);
	}
	return (1);
}

int	get_x_of_start(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				return (j);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

int	get_y_of_start(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}
