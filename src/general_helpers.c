/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 13:18:19 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/09 13:18:37 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}

void	find_player(t_map *map, t_player *player)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (map->map[row])
	{
		column = 0;
		while (map->map[row][column])
		{
			if (is_player(map->map[row][column]))
			{
				init_player(player, row, column, map->map[row][column]);
				return ;
			}
			column++;
		}
		row++;
	}
}
